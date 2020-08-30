
import React from 'react';

import styles from './DataSourcePanel.module.css';
import { ChannelsConsumer } from '../state/Channels';
import { DatalogsConsumer } from '../state/Datalogs';
import { NUM_ADCS, CHANNELS_PER_ADC } from '../util/constants.js';
import ChannelSettings from './ChannelSettings';
import Graph from './Graph';
import { COLORS } from '../util/constants';
import UpdateIcon from '@material-ui/icons/Update';
import FileIcon from '@material-ui/icons/InsertDriveFile';

export default class DataSourcePanel extends React.Component {
  render() {
    return (<DatalogsConsumer>{datalogsStore => {
      let children = [(<div className={styles.card}>
        <span><UpdateIcon /></span>
        <span className={styles.filename}>Now</span>
        <span></span>
        <span className={styles.description}>realtime</span>
      </div>)];
      for (const datalog of datalogsStore.datalogs) {
        let date = datalog.date;
        let formattedDate = `${date.getDate()}-${date.getMonth()}-${date.getFullYear()} ${date.getHours()}:${date.getMinutes()}`;
        let duration = datalog.duration;
        // Oh god my eyes are on fire.
        let formattedDuration = `${Math.floor(duration / 3600)}h${Math.floor(duration / 60 % 60).toString().padStart(2, '0')}m${Math.floor(duration % 60).toString().padStart(2, '0')}s`
        children.push((<div className={styles.card}>
          <span><FileIcon /></span>
          <span className={styles.filename}>{formattedDate}</span>
          <span></span>
          <span className={styles.description}>{formattedDuration}</span>
        </div>));
      }
      return (<div className={styles.root}>
        <div className={styles.grid}>
          {children}
        </div>
      </div>);
    }}</DatalogsConsumer>);
  }
}