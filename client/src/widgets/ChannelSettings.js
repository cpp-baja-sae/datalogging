import MenuItem from '@material-ui/core/MenuItem';
import React from 'react';
import TextField from '@material-ui/core/TextField';

import { UNITS, UNIT_ABBREVIATIONS } from '../util/constants';
import styles from './ChannelSettings.module.css';
import { ChannelsConsumer } from '../state/Channels';

class ChannelSettings extends React.Component {
  patchSettings(patch) {
    let settings = this.props.settings;
    for (let key in patch) {
      settings[key] = patch[key];
    }
    this.props.onChange(settings);
  }

  renderSettings(settings, patchSettings) {
    let unitOptions = [];
    for (let unit of UNITS) {
      unitOptions.push((
        <MenuItem key={unit} value={unit}>{unit} ({UNIT_ABBREVIATIONS[unit]})</MenuItem>
      ));
    }

    let setMinValue = text => {
      let result = parseFloat(text);
      if (isNaN(result)) {
        patchSettings({});
      } else {
        patchSettings({ minValue: result });
      }
    };
    let setMaxValue = text => {
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
          if (event.key === 'Enter') setMinValue(event.target.value);
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
          if (event.key === 'Enter') setMaxValue(event.target.value);
        }}
        onBlur={event => {
          setMaxValue(event.target.value);
        }}
      />
    </form>)
  }

  render() {
    return (<ChannelsConsumer>{channelStore => {
      let settings = channelStore.channels[this.props.index];
      let patchSettings = patch => channelStore.patchChannel(this.props.index, patch);
      return this.renderSettings(settings, patchSettings);
    }}</ChannelsConsumer>);
  }
}

export default ChannelSettings;
