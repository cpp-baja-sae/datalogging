import React from 'react';

import styles from './ValueTooltip.module.css';
import mousePos from '../util/mousePos';
import { LayoutConsumer } from '../state/Layout';
import realtimeBufferStore from '../data/realtimeBufferStore.js';
import { ChannelsConsumer } from '../state/Channels';
import { COLORS, UNIT_ABBREVIATIONS } from '../util/constants';

export default class ValueTooltip extends React.Component {
  constructor(props) {
    super(props);
  }

  setupTooltip(element) {
    if (this.currentInterval) {
      clearInterval(this.currentInterval);
    }
    if (!element) return;

    this.currentInterval = setInterval(() => {
      if (mousePos.x <= mousePos.graphStartX || mousePos.x >= mousePos.graphEndX) {
        element.style = 'display: none';
        return;
      }
      let top = mousePos.y - 8;
      if (mousePos.x > window.innerWidth / 2) {
        let right = window.innerWidth - mousePos.x + 16;
        element.style = `right: ${right}px; top: ${top}px`;
      } else {
        let left = mousePos.x + 24;
        element.style = `left: ${left}px; top: ${top}px`;
      }

      for (let graphIndex = 0; graphIndex < this.layout.graphs.length; graphIndex++) {
        let graph = this.layout.graphs[graphIndex];
        let channel = this.channelStore.channels[graph.channel];
        let div = element.children[graphIndex];
        let time = (mousePos.x - mousePos.graphEndX) * 0.001;
        let value = realtimeBufferStore.getValue(graph.channel, time);
        value = value * (channel.maxValue - channel.minValue) + channel.minValue;
        let abbr = UNIT_ABBREVIATIONS[channel.units];
        div.children[2].innerText = value.toPrecision(4) + abbr;
      }
    }, 50);
  }

  render() {
    return (<LayoutConsumer>{layout => (<ChannelsConsumer>{channelStore => {
      this.layout = layout;
      this.channelStore = channelStore;
      let values = [];
      for (let graph of layout.graphs) {
        let channel = channelStore.channels[graph.channel];
        values.push((<div key={graph.key} className={styles.row}>
          <span className={styles.label} style={{color: COLORS[graph.color]}}>
            {channel.label}:
          </span>
          <span className={styles.spacer} />
          <span className={styles.value}>0</span>
        </div>))
      }
      return (<div className={styles.root} ref={e => this.setupTooltip(e)}>
        {values}
      </div>);
    }}</ChannelsConsumer>)}</LayoutConsumer>);
  }
}