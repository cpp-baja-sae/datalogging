import React from 'react';

import styles from './ChannelPanel.module.css';
import ChannelSettingsEditor from './ChannelSettings';
import Graph from './Graph';
import { COLORS } from '../util/constants';
import dataInterface from '../data/dataInterface';

export default class ChannelPanel extends React.Component {
  listener: () => void;

  constructor(props: Readonly<{}>) {
    super(props);
    this.listener = () => this.forceUpdate();
  }

  componentDidMount() {
    dataInterface.addSettingsListener(this.listener);
  }

  componentWillUnmount() {
    dataInterface.removeSettingsListener(this.listener);
  }

  render() {
    let channelCards = [];
    let index = 0;
    for (let channel of dataInterface.getFormat().layout) {
      channelCards.push((<div className={styles.card} key={index.toString()}>
        <div className={styles.identifier}>{`${channel.group} / ${channel.name}`}</div>
        <ChannelSettingsEditor index={index} />
        <div className={styles.graphContainer}>
          <Graph channel={index} color={COLORS[0]} />
        </div>
      </div>));
      index++;
    }

    return (<div className={styles.root}>
      {channelCards}
    </div>);
  }
}