import React from 'react';

import styles from './CsvExportPanel.module.css';
import { DataFormat } from '../data/types';
import { settings, estimateCsvSize, getCsvLink } from '../util/backend';
import { TextField, MenuItem, TextFieldProps, FormControlLabel, Checkbox, Button } from '@material-ui/core';
import { frameSizeFromFormat } from '../data/frame';
import { formatMetricValue } from '../util/misc';
import dataInterface from '../data/dataInterface';
import MaskedInput from 'react-text-mask';

function TimeInputImpl(props: TextFieldProps, context?: any) {
  const { inputRef, ...other } = props;

  return (
    <MaskedInput
      {...(other as any)}
      ref={(ref) => {
        // Ew.
        if (inputRef) (inputRef as (ref: any) => void)(ref ? ref.inputElement : null);
      }}
      mask={[/\d/, /\d/, ':', /\d/, /\d/, ':', /\d/, /\d/, '.', /\d/]}
      placeholderChar={'\u2000'}
      showMask
    />
  );
}

type CsvExportPanelState = {
  selectedLod: number,
  startTime: string,
  endTime: string,
  channels: Array<boolean>,
  estimate: number,
  estimateLoading: boolean,
};

export default class CsvExportPanel extends React.Component<{}, CsvExportPanelState> {
  listener: () => void;

  constructor(props: Readonly<{}>) {
    super(props);
    this.listener = () => this.forceUpdate();
    this.state = {
      selectedLod: 0,
      startTime: '00:00:00.0',
      endTime: '00:00:30.0',
      // We don't really know how many channels the current datalog will have so just allocate a 
      // big array so we don't have to resize it all the time.
      channels: new Array(500),
      estimate: 0,
      estimateLoading: false,
    };
    for (let i = 0; i < 500; i++) {
      this.state.channels[i] = false;
    }
  }

  componentDidMount() {
    dataInterface.addSettingsListener(this.listener);
  }

  componentWillUnmount() {
    dataInterface.removeSettingsListener(this.listener);
  }

  parseTime(time: string): number {
    let hours = parseInt(time.substring(0, 2));
    let minutes = parseInt(time.substring(3, 5));
    let seconds = parseFloat(time.substring(6));
    return (hours * 60 + minutes) * 60 + seconds;
  }

  timeToIndex(time: number, lod: number, format: DataFormat): number {
    let frequency = (1000 * 1000) / format.frame_time_us;
    frequency /= Math.pow(format.lod_sample_interval, lod);
    return Math.floor(time * frequency);
  }

  reloadEstimate() {
    this.setState({ ...this.state, estimateLoading: true });
    let lod = this.state.selectedLod;
    let format = dataInterface.getFormat();
    let start = this.timeToIndex(this.parseTime(this.state.startTime), lod, format);
    let end = this.timeToIndex(this.parseTime(this.state.endTime), lod, format);
    let channels = [];
    for (let i = 0; i < format.layout.length; i++) {
      if (this.state.channels[i]) {
        channels.push(i);
      }
    }
    (async () => {
      let sizeEstimate = await estimateCsvSize((format as any).date, start, end, lod, channels);
      this.setState({ ...this.state, estimateLoading: false, estimate: sizeEstimate });
    })();
  }

  csvLink() {
    let lod = this.state.selectedLod;
    let format = dataInterface.getFormat();
    let start = this.timeToIndex(this.parseTime(this.state.startTime), lod, format);
    let end = this.timeToIndex(this.parseTime(this.state.endTime), lod, format);
    let channels = [];
    for (let i = 0; i < format.layout.length; i++) {
      if (this.state.channels[i]) {
        channels.push(i);
      }
    }
    return getCsvLink((format as any).date, start, end, lod, channels);
  }

  render() {
    if (dataInterface.isSourceRealtime()) {
      return (<div className={styles.root}>
        CSV export only works on pre-recorded datalogs. Open one by clicking the
        open button on the top left of the toolbar.
      </div>);
    }

    // Else...
    let format = dataInterface.getFormat();
    let options = [];
    let frequency = (1000 * 1000) / format.frame_time_us;
    for (let lod = 0; lod < format.total_num_lods; lod++) {
      let title = formatMetricValue(frequency, 'Hz');
      options.push((<MenuItem key={lod} value={lod}>{title}</MenuItem>));
      frequency /= format.lod_sample_interval;
    }
    let channelCheckboxes = [];
    for (let channel = 0; channel < format.layout.length; channel++) {
      let name = format.layout[channel].group + '/' + format.layout[channel].name;
      let callback = (event: React.ChangeEvent<HTMLInputElement>) => {
        this.setState((state) => {
          state.channels[channel] = !state.channels[channel];
          return state;
        }, () => {
          this.reloadEstimate();
        })
      };
      channelCheckboxes.push((<FormControlLabel
        key={channel}
        control={<Checkbox checked={this.state.channels[channel]} onChange={callback} name={name} />}
        label={name}
      />));
    }
    let frameSize = frameSizeFromFormat(format);
    return (<div className={styles.root}>
      <form noValidate autoComplete="off" className={styles.form}>
        <div className={styles.column}>
          <TextField
            id="start-time"
            label="Start Time"
            variant="outlined"
            value={this.state.startTime}
            onChange={event => {
              this.setState({ ...this.state, startTime: event.target.value }, () => {
                this.reloadEstimate();
              });
            }}
            InputProps={{
              inputComponent: TimeInputImpl as any
            }}
          />
          <TextField
            id="end-time"
            label="End Time"
            variant="outlined"
            value={this.state.endTime}
            onChange={event => {
              this.setState({ ...this.state, endTime: event.target.value }, () => {
                this.reloadEstimate();
              });
            }}
            InputProps={{
              inputComponent: TimeInputImpl as any
            }}
          />
          <TextField
            select
            id="resolution"
            label="Data Resolution"
            variant="outlined"
            value={this.state.selectedLod}
            onChange={event => {
              let value = parseInt(event.target.value);
              this.setState({ ...this.state, selectedLod: value }, () => {
                this.reloadEstimate();
              });
            }}
            className={styles.dropdown}
          >
            {options}
          </TextField>
          <div>{
            this.state.estimateLoading
              ? "Loading estimate..."
              : "Estimated size: " + formatMetricValue(this.state.estimate, 'B')
          }</div>
          <Button variant="contained" color="primary" href={this.csvLink()}>
            Download
          </Button>
        </div>
        <div className={styles.czech_column}>
          {channelCheckboxes}
        </div>
      </form>
    </div>);
  }
}