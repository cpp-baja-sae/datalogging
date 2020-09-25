import React from 'react';

import styles from './SettingsPanel.module.css';
import { DataFormat } from '../data/types';
import { settings } from '../util/backend';
import { TextField, MenuItem } from '@material-ui/core';
import { frameSizeFromFormat } from '../data/frame';
import { formatMetricValue } from '../util/misc';

type SettingsPanelState = {
  format: DataFormat | null,
  currentLod: number,
  loading: boolean,
};

export default class SettingsPanel extends React.Component<{}, SettingsPanelState> {
  streamLodListener: (streamLod: number) => void;

  constructor(props: Readonly<{}>) {
    super(props);
    this.state = {
      format: null,
      currentLod: 0,
      loading: true,
    };
    this.streamLodListener = (streamLod) => this.setState({
      ...this.state,
      currentLod: streamLod,
      loading: false,
    })
  }

  componentDidMount() {
    (async () => {
      settings.stream_lod.subscribe(this.streamLodListener);
      let format = await settings.default_format.getOnce();
      let lod = await settings.stream_lod.getOnce();
      this.setState({ format, currentLod: lod, loading: false });
    })();
  }

  componentWillUnmount() {
    settings.stream_lod.unsubscribe(this.streamLodListener);
  }

  render() {
    let streamLodDropdown;
    if (!this.state.loading && this.state.format) {
      let options = [];
      let frequency = (1000 * 1000) / this.state.format.frame_time_us;
      let frameSize = frameSizeFromFormat(this.state.format);
      let bitsPerSecond = frameSize * 8 * frequency;
      for (let lod = 0; lod < this.state.format.total_num_lods; lod++) {
        // LODs that are not max resolution have 3 sub frames for min, max, avg.
        let multiplier = lod == 0 ? 1 : 3;
        let title = formatMetricValue(frequency, 'Hz') 
          + ' / ' + formatMetricValue(bitsPerSecond * multiplier, 'bps');
        options.push((<MenuItem key={lod} value={lod}>{title}</MenuItem>));
        frequency /= this.state.format.lod_sample_interval;
        bitsPerSecond /= this.state.format.lod_sample_interval;
      }
      streamLodDropdown = (<TextField
        select
        id="lod"
        label="Stream Resolution"
        variant="outlined"
        value={this.state.currentLod}
        onChange={event => {
          let value = parseInt(event.target.value);
          (async () => {
            this.setState({ ...this.state, loading: true });
            await settings.stream_lod.set(value);
          })();
        }}
        className={styles.dropdown}
      >
        {options}
      </TextField>);
    } else {
      streamLodDropdown = (<TextField
        select
        id="lod"
        label="Stream Resolution"
        variant="outlined"
        value={0}
        disabled={true}
        onChange={event => null}
        className={styles.dropdown}
      >
        <MenuItem key={0} value={0} disabled={true}>Loading...</MenuItem>
      </TextField>);
    }
    return (<div className={styles.root}>
      <form noValidate autoComplete="off" className={styles.grid}>
        {streamLodDropdown}
      </form>
    </div>);
  }
}