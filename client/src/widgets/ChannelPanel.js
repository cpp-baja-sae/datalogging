import React from 'react';

import styles from './ChannelPanel.module.css';
import { ChannelsConsumer } from '../state/Channels';
import { NUM_ADCS, CHANNELS_PER_ADC } from '../util/constants.js';
import ChannelSettings from './ChannelSettings';
import Graph from './Graph';
import { COLORS } from '../util/constants';

export default class ChannelPanel extends React.Component {
  render() {
    return (<ChannelsConsumer>{channelStore => {
      let channelCards = [];
      for (let adc = 0; adc < NUM_ADCS; adc++) {
        for (let adcChannel = 0; adcChannel < CHANNELS_PER_ADC; adcChannel++) {
          let channel = adcChannel * NUM_ADCS + adc;
          channelCards.push((<div className={styles.card} key={channel}>
            <div className={styles.identifier}>{`ADC${adc + 1} / CHN${adcChannel + 1}`}</div>
            <ChannelSettings index={channel} />
            <div className={styles.graphContainer}>
              <Graph channel={channel} color={COLORS[0]} />
            </div>
          </div>));
        }
      }

      return (<div className={styles.root}>
        {channelCards}
      </div>);
    }}</ChannelsConsumer>);
  }
}