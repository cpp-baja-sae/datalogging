import MenuItem from '@material-ui/core/MenuItem';
import React from 'react';
import TextField from '@material-ui/core/TextField';

import { UNITS, UNIT_ABBREVIATIONS } from '../util/constants';
import { LayoutConsumer, ChannelSettings, LayoutState } from '../state/Layout';
import styles from './ChannelSettings.module.css';
import dataInterface from '../data/dataInterface';

type ChannelSettingsProps = {
  index: number,
};

class ChannelSettingsEditor extends React.Component<ChannelSettingsProps> {
  listener: () => void;

  constructor(props: Readonly<ChannelSettingsProps>) {
    super(props);
    this.listener = () => this.forceUpdate();
  }

  componentDidMount() {
    dataInterface.addSettingsListener(this.listener);
  }

  componentWillUnmount() {
    dataInterface.removeSettingsListener(this.listener);
  }

  renderSettings(settings: ChannelSettings, patchSettings: (patch: Partial<ChannelSettings>) => void) {
    let unitOptions = [];
    for (let unit of UNITS) {
      unitOptions.push((
        <MenuItem key={unit} value={unit}>{unit} ({UNIT_ABBREVIATIONS[unit]})</MenuItem>
      ));
    }

    let setMinValue = (text: string) => {
      let result = parseFloat(text);
      if (isNaN(result)) {
        patchSettings({});
      } else {
        patchSettings({ minValue: result });
      }
    };
    let setMaxValue = (text: string) => {
      let result = parseFloat(text);
      if (isNaN(result)) {
        patchSettings({});
      } else {
        patchSettings({ maxValue: result });
      }
    };

    return (<form noValidate autoComplete="off" className={styles.root}>
      <TextField
        id="label"
        label="Label"
        variant="outlined"
        value={settings.label}
        onChange={event => patchSettings({ label: event.target.value })}
      />
      <TextField
        select
        id="units"
        label="Units"
        variant="outlined"
        value={settings.units}
        onChange={event => patchSettings({ units: event.target.value })}
      >
        {unitOptions}
      </TextField>
      <TextField
        key={`min${settings.minValue}`}
        id="min"
        label="Min. Value (@0V)"
        variant="outlined"
        defaultValue={settings.minValue}
        onKeyDown={event => {
          if (event.key === 'Enter') setMinValue((event.target as any).value);
        }}
        onBlur={event => {
          setMinValue(event.target.value);
        }}
      />
      <TextField
        key={`max${settings.minValue}`}
        id="max"
        label="Max. Value (@5V)"
        variant="outlined"
        defaultValue={settings.maxValue}
        onKeyDown={event => {
          if (event.key === 'Enter') setMaxValue((event.target as any).value);
        }}
        onBlur={event => {
          setMaxValue(event.target.value);
        }}
      />
    </form>)
  }

  render() {
    return (<LayoutConsumer>{layoutIn => {
      let layout = layoutIn as LayoutState;
      let settings = layout.channelSettings[this.props.index];
      let patchSettings = (patch: Partial<ChannelSettings>) => layout.patchChannel(this.props.index, patch);
      return this.renderSettings(settings, patchSettings);
    }}</LayoutConsumer>);
  }
}

export default ChannelSettingsEditor;
