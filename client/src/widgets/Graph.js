import React from 'react';

import styles from './Graph.module.css';
import dataSourceInterface from '../data/dataSourceInterface';
import mousePos from '../util/mousePos';

class Graph extends React.Component {
    componentDidMount() {
        this.listener = () => this.renderData();
        this.resizeListener = () => this.forceUpdate();
        dataSourceInterface.addListener(this.listener);
        window.addEventListener('resize', this.resizeListener);
    }

    onCanvasChange(newCanvas) {
        if (!newCanvas) return;
        const canvas = newCanvas;
        const wrapper = canvas.parentElement;
        canvas.width = wrapper.clientWidth;
        canvas.height = wrapper.clientHeight;
        let bounds = canvas.getBoundingClientRect();
        mousePos.graphStartX = bounds.left;
        mousePos.graphEndX = bounds.right;

        this.context = canvas.getContext('2d');
        this.renderData();
    }

    componentWillUnmount() {
        dataSourceInterface.removeListener(this.listener);
        window.removeEventListener('resize', this.resizeListener);
    }

    renderData() {
        let channel = this.props.channel;

        const width = this.context.canvas.width;
        const readStep = dataSourceInterface.getTimePerPixel();
        const leftmostTimeIndex = -width * readStep + dataSourceInterface.getViewPosition();
        const height = this.context.canvas.height;

        this.context.clearRect(0, 0, width, height);
        let y = value => (1 - value) * height;
        let readFrom;

        this.context.fillStyle = this.props.color;
        this.context.strokeStyle = this.props.color;
        this.context.lineWidth = 2;

        if (this.props.showBounds) {
            readFrom = leftmostTimeIndex;
            this.context.globalAlpha = 0.2;
            this.context.beginPath();
            this.context.moveTo(0, y(dataSourceInterface.getMin(channel, readFrom)));
            for (let x = 1; x < width; x++) {
                readFrom += readStep;
                this.context.lineTo(x, y(dataSourceInterface.getMin(channel, readFrom)) + 1);
            }
            for (let x = width - 1; x >= 0; x--) {
                this.context.lineTo(x, y(dataSourceInterface.getMax(channel, readFrom)) - 1);
                readFrom -= readStep;
            }
            this.context.closePath();
            this.context.fill();
        }

        readFrom = leftmostTimeIndex;
        this.context.globalAlpha = 1;
        this.context.beginPath();
        this.context.moveTo(0, y(dataSourceInterface.getValue(channel, readFrom)));
        for (let x = 1; x < width; x++) {
            readFrom += readStep;
            this.context.lineTo(x, y(dataSourceInterface.getValue(channel, readFrom)));
        }
        this.context.lineJoin='bevel';
        this.context.stroke();

        if (!this.props.showCursor) return;

        let curx = mousePos.x;
        curx -= this.context.canvas.getBoundingClientRect().left;
        curx -= 0.5;
        this.context.strokeStyle = 'white';
        this.context.lineWidth = 1;
        this.context.beginPath();
        this.context.moveTo(curx, 0);
        this.context.lineTo(curx, height);
        this.context.stroke();
        let time = (curx - width) * readStep;
        let cury = y(dataSourceInterface.getValue(channel, time));
        this.context.fillStyle = 'white';
        this.context.beginPath();
        this.context.ellipse(curx, cury, 4, 4, 0, 0, Math.PI * 2.0);
        this.context.fill();
        this.context.fillStyle = this.props.color;
        this.context.beginPath();
        this.context.ellipse(curx, cury, 3, 3, 0, 0, Math.PI * 2.0);
        this.context.fill();
    }

    render() {
        return (
            <div ref='wrapper' className={styles.wrapper}>
                <canvas ref={this.onCanvasChange.bind(this)} width={0} height={0} />
            </div>
        );
    }
}

export default Graph;