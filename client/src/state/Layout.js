import React from "react";

const { Provider, Consumer } = React.createContext();

export class LayoutProvider extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      graphs: [
        {
          channel: 0,
          color: 0,
          key: '' + Math.random(),
        },
        {
          channel: 2,
          color: 0,
          key: '' + Math.random(),
        }
      ],
      channelSettings: [],
      patchChannel: (index, patch) => this.setState(oldState => {
        for (let key in patch) {
          oldState.channelSettings[index][key] = patch[key];
        }
        return oldState;
      }),
      changeGraph: (index, newSettings) => this.setState(oldState => {
        oldState.graphs[index] = newSettings;
        return oldState;
      }),
      patchGraph: (index, patch) => this.setState(oldState => {
        for (let key in patch) {
          oldState.graphs[index][key] = patch[key];
        }
        return oldState;
      }),
      newGraph: () => this.setState(oldState => {
        oldState.graphs.push({ adc: 0, channel: 0, color: 0, key: '' + Math.random() });
        return oldState;
      }),
      deleteGraph: key => this.setState(oldState => {
        oldState.graphs = oldState.graphs.filter(graph => graph.key !== key);
        return oldState;
      }),
    };
    for (let i = 0; i < 32; i++) {
      this.state.channelSettings.push({ 
        label: 'unlabeled',
        minValue: 0,
        maxValue: 5,
        units: 'Volts'
      });
    }
    for (let i = 0; i < 8; i++) {
      this.state.channelSettings.push({ 
        label: 'unlabeled',
        minValue: 0,
        maxValue: 0,
        units: 'Volts'
      });
    }
  }

  render() {
    return (<Provider value={this.state}>{this.props.children}</Provider>);
  }
}

export const LayoutConsumer = Consumer;