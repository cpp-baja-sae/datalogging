import React from "react";

import { NUM_ADCS, NUM_CHANNELS, CHANNELS_PER_ADC } from '../util/constants.js';

const { Provider, Consumer } = React.createContext();

export class ChannelsProvider extends React.Component {
  constructor(props) {
    super(props);

    let channels = [];
    for (let i = 0; i < NUM_CHANNELS; i++) {
      channels.push({
        label: `Channel ${i % NUM_ADCS + 1}.${Math.floor(i / NUM_ADCS)+ 1}`,
        units: 'Volts',
        minValue: 0.0,
        maxValue: 5.0,
      });
    }

    this.state = { channels: channels };
  }

  render() {
    let provide = {
      channels: this.state.channels,
      changeChannel: (index, newSettings) => this.setState(oldState => {
        oldState.channels[index] = newSettings;
        return oldState;
      }),
      patchChannel: (index, patch) => this.setState(oldState => {
        for (let key in patch) {
          oldState.channels[index][key] = patch[key];
        }
        return oldState;
      }),
    };

    return (<Provider value={provide}>{this.props.children}</Provider>);
  }
}

export const ChannelsConsumer = Consumer;