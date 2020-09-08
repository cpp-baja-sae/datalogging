import React from "react";

import { getAvailableLogs } from '../util/backend';

export type DatalogsState = {
  datalogs: Array<any>
};

const { Provider, Consumer } = React.createContext<Readonly<DatalogsState> | undefined>(undefined);

export class DatalogsProvider extends React.Component<{}, DatalogsState> {
  constructor(props: Readonly<{}>) {
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