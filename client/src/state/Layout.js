import React from "react";

const { Provider, Consumer } = React.createContext();

export class LayoutProvider extends React.Component {
  state = {
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
  }

  render() {
    let provide = {
      graphs: this.state.graphs,
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

    return (<Provider value={provide}>{this.props.children}</Provider>);
  }
}

export const LayoutConsumer = Consumer;