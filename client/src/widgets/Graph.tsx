import React from 'react';

import styles from './Graph.module.css';
import dataInterface from '../data/dataInterface';
import mousePos from '../util/mousePos';

type GraphProps = {
  channel: number,
  color: string,
  showBounds?: boolean,
  showCursor?: boolean,
};

class Graph extends React.Component<GraphProps> {
  listener: () => void;
  resizeListener: () => void;

  constructor(props: Readonly<GraphProps>) {
    super(props);
    this.listener = () => this.forceUpdate();
    this.resizeListener = () => this.forceUpdate();
  }

  componentDidMount() {
    dataInterface.addListener(this.listener);
    window.addEventListener('resize', this.resizeListener);
  }

  onCanvasChange(newCanvas: HTMLCanvasElement) {
    if (!newCanvas) return;
    const canvas = newCanvas;
    const wrapper = canvas.parentElement as HTMLElement;
    canvas.width = wrapper.clientWidth;
    canvas.height = wrapper.clientHeight;
    let bounds = canvas.getBoundingClientRect();
    mousePos.graphStartX = bounds.left;
    mousePos.graphEndX = bounds.right;

    this.context = canvas.getContext('2d');
    this.renderData();
  }

  componentWillUnmount() {
    dataInterface.removeListener(this.listener);
    window.removeEventListener('resize', this.resizeListener);
  }

  renderData() {
    let channel = this.props.channel;

    const width = this.context.canvas.width;
    const readStep = dataInterface.getTimePerPixel();
    const leftmostTimeIndex = 
      dataInterface.isSourceRealtime() 
      ? -width * readStep + dataInterface.getViewPosition() 
      : dataInterface.getViewPosition();
    const height = this.context.canvas.height;

    this.context.clearRect(0, 0, width, height);
    let y = (value: number) => (1 - value) * height;
    let readFrom;

    this.context.fillStyle = this.props.color;
    this.context.strokeStyle = this.props.color;
    this.context.lineWidth = 2;

    if (this.props.showBounds) {
      readFrom = leftmostTimeIndex;
      this.context.globalAlpha = 0.2;
      this.context.beginPath();
      this.context.moveTo(0, y(dataInterface.getMin(readFrom, channel)));
      for (let x = 1; x < width; x++) {
        readFrom += readStep;
        this.context.lineTo(x, y(dataInterface.getMin(readFrom, channel)) + 1);
      }
      for (let x = width - 1; x >= 0; x--) {
        this.context.lineTo(x, y(dataInterface.getMax(readFrom, channel)) - 1);
        readFrom -= readStep;
      }
      this.context.closePath();
      this.context.fill();
    }

    readFrom = leftmostTimeIndex;
    this.context.globalAlpha = 1;
    this.context.beginPath();
    this.context.moveTo(0, y(dataInterface.getValue(readFrom, channel)));
    for (let x = 1; x < width; x++) {
      readFrom += readStep;
      this.context.lineTo(x, y(dataInterface.getValue(readFrom, channel)));
    }
    this.context.lineJoin = 'bevel';
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
    let time = curx * readStep + leftmostTimeIndex;
    let cury = y(dataInterface.getValue(time, channel));
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