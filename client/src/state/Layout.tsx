import React from "react";

export type GraphSettings = {
  channel: number,
  color: number,
  key: string
};
export type ChannelSettings = {
  label: string,
  minValue: number,
  maxValue: number,
  units: string,
};
export type LayoutState = {
  graphs: Array<GraphSettings>,
  channelSettings: Array<ChannelSettings>,
  patchChannel: (index: number, patch: Partial<ChannelSettings>) => void,
  changeGraph: (index: number, graph: GraphSettings) => void,
  patchGraph: (index: number, patch: Partial<GraphSettings>) => void,
  newGraph: () => void,
  deleteGraph: (key: string) => void,
}

const { Provider, Consumer } = React.createContext<LayoutState | undefined>(undefined);

export class LayoutProvider extends React.Component<{}, LayoutState> {
  constructor(props: Readonly<{}>) {
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
          (oldState.channelSettings[index] as any)[key] = (patch as any)[key];
        }
        return oldState;
      }),
      changeGraph: (index, newSettings) => this.setState(oldState => {
        oldState.graphs[index] = newSettings;
        return oldState;
      }),
      patchGraph: (index, patch) => this.setState(oldState => {
        for (let key in patch) {
          (oldState.graphs[index] as any)[key] = (patch as any)[key];
        }
        return oldState;
      }),
      newGraph: () => this.setState(oldState => {
        oldState.graphs.push({ channel: 0, color: 0, key: '' + Math.random() });
        return oldState;
      }),
      deleteGraph: key => this.setState(oldState => {
        let newGraphs = oldState.graphs.filter(graph => graph.key !== key);
        return {
          ...oldState,
          graphs: newGraphs
        };
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