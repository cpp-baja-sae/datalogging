import React from 'react';

import styles from './ValueTooltip.module.css';
import mousePos from '../util/mousePos';
import { LayoutConsumer } from '../state/Layout';
import { COLORS, UNIT_ABBREVIATIONS } from '../util/constants';
import dataInterface from '../data/dataInterface';
import { LayoutState } from '../state/Layout';

export default class ValueTooltip extends React.Component {
  listener: () => void;
  layout?: LayoutState;
  currentInterval: NodeJS.Timeout | undefined;

  componentDidMount() {
    dataInterface.addSettingsListener(this.listener);
  }

  componentWillUnmount() {
    dataInterface.removeSettingsListener(this.listener);
  }

  constructor(props: Readonly<{}>) {
    super(props);
    this.listener = () => this.forceUpdate();
  }

  setupTooltip(element: HTMLDivElement) {
    if (this.currentInterval) {
      clearInterval(this.currentInterval);
    }
    if (!element) return;

    this.currentInterval = setInterval(() => {
      if (mousePos.x <= mousePos.graphStartX || mousePos.x >= mousePos.graphEndX) {
        element.style.display = 'none';
        return;
      } else {
        element.style.display = '';
      }
      let top = mousePos.y - 8;
      element.style.top = top + 'px';
      if (mousePos.x > window.innerWidth / 2) {
        let right = window.innerWidth - mousePos.x + 16;
        element.style.left = '';
        element.style.right = right + 'px';
      } else {
        let left = mousePos.x + 24;
        element.style.right = '';
        element.style.left = left + 'px';
      }

      let layout = this.layout as LayoutState;
      for (let graphIndex = 0; graphIndex < layout.graphs.length; graphIndex++) {
        let graph = layout.graphs[graphIndex];
        let channelSettings = layout.channelSettings[graph.channel];
        let div = element.children[graphIndex];
        let time;
        if (dataInterface.isSourceRealtime()) {
          time = (mousePos.x - mousePos.graphEndX);
        } else {
          time = (mousePos.x - mousePos.graphStartX);
        }
        time = time * dataInterface.getTimePerPixel() + dataInterface.getViewPosition();
        let value = dataInterface.getValue(time, graph.channel);
        value = value * (channelSettings.maxValue - channelSettings.minValue) + channelSettings.minValue;
        let abbr = UNIT_ABBREVIATIONS[channelSettings.units];
        div.children[2].textContent = value.toPrecision(4) + abbr;
      }
    }, 50);
  }

  render() {
    return (<LayoutConsumer>{layoutIn => {
      let layout = layoutIn as LayoutState;
      this.layout = layout;
      let values = [];
      for (let graph of layout.graphs) {
        let channelSettings = layout.channelSettings[graph.channel];
        values.push((<div key={graph.key} className={styles.row}>
          <span className={styles.label} style={{ color: COLORS[graph.color] }}>
            {channelSettings.label}:
          </span>
          <span className={styles.spacer} />
          <span className={styles.value}>0</span>
        </div>))
      }
      return (<div className={styles.root} ref={e => e ? this.setupTooltip(e) : null}>
        {values}
      </div>);
    }}</LayoutConsumer>);
  }
}