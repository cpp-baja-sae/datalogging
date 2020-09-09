
import React from 'react';

import styles from './DataSourcePanel.module.css';
import { DatalogsConsumer, DatalogsState } from '../state/Datalogs';
import UpdateIcon from '@material-ui/icons/Update';
import FileIcon from '@material-ui/icons/InsertDriveFile';
import { DatalogInfo } from '../data/types';
import dataInterface from '../data/dataInterface';
import { withRouter, RouteComponentProps } from 'react-router-dom';
import { formatDate } from '../util/misc';

class DataSourcePanel extends React.Component<RouteComponentProps> {
  render() {
    const openRealtime = () => {
      dataInterface.useRealtimeSource();
      this.props.history.push('/graphs');
    }
    const openDatalog = (datalog: DatalogInfo) => {
      dataInterface.useDatalogSource(datalog);
      this.props.history.push('/graphs');
    };
    return (<DatalogsConsumer>{datalogsStoreIn => {
      let datalogsStore = datalogsStoreIn as DatalogsState;
      let children = [(<div className={styles.card} key="realtime" onClick={event => openRealtime()}>
        <span><UpdateIcon /></span>
        <span className={styles.filename}>Now</span>
        <span></span>
        <span className={styles.description}>realtime</span>
      </div>)];
      for (const datalog of datalogsStore.datalogs) {
        let date = datalog.jsdate;
        let formattedDate = formatDate(date);
        let duration = datalog.duration;
        // Oh god my eyes are on fire.
        let formattedDuration = `${Math.floor(duration / 3600)}h${Math.floor(duration / 60 % 60).toString().padStart(2, '0')}m${Math.floor(duration % 60).toString().padStart(2, '0')}s`
        children.push((<div className={styles.card} onClick={event => openDatalog(datalog)} key={datalog.date}>
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

export default withRouter(DataSourcePanel);