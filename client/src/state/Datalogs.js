import React from "react";

import { NUM_ADCS, NUM_CHANNELS, CHANNELS_PER_ADC } from '../util/constants.js';
import { getAvailableLogs } from '../util/backend.js';

const { Provider, Consumer } = React.createContext();

export class DatalogsProvider extends React.Component {
  constructor(props) {
    super(props);

    this.state = { datalogs: [] };
  }

  componentDidMount() {
    (async () => {
      let datalogs = (await getAvailableLogs()).list;
      for (let datalog of datalogs) {
        datalog.key = datalog.date;
        datalog.date = new Date(parseInt(datalog.date) * 1000);
      }
      this.setState({ datalogs });
    })();
  }

  render() {
    return (<Provider value={this.state}>{this.props.children}</Provider>);
  }
}

export const DatalogsConsumer = Consumer;