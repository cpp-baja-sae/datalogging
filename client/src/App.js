import { createMuiTheme } from '@material-ui/core/styles';
import React from 'react';
import { ThemeProvider } from '@material-ui/styles';
import {
  BrowserRouter as Router,
  Switch,
  Route,
  Link,
  Redirect
} from "react-router-dom";

import './App.css';
import styles from './styles.module.css';

import Border from './widgets/Border';
import GraphPanel from './widgets/GraphPanel';
import ChannelPanel from './widgets/ChannelPanel';
import DataSourcePanel from './widgets/DataSourcePanel';
import Header from './widgets/Header';
import { LayoutProvider } from './state/Layout';
import { ChannelsProvider } from './state/Channels';
import { DatalogsProvider } from './state/Datalogs';

class App extends React.Component {

  render() {
    const theme = createMuiTheme({
      palette: {
        type: 'dark'
      }
    });
    return (
      <ThemeProvider theme={theme}><LayoutProvider><ChannelsProvider><DatalogsProvider><Router>
        <Route exact path="/"><Redirect to="/graphs" /></Route>
        <div className={'App ' + styles.surface}>
          <Header />
          <Border />
          <div className="scrollPane">
            <Switch>
              <Route path="/graphs">
                <GraphPanel />
              </Route>
              <Route path="/channels">
                <ChannelPanel />
              </Route>
              <Route path="/pickDataSource">
                <DataSourcePanel />
              </Route>
            </Switch>
          </div>
          <Border />
          <div>Ruler</div>
        </div>
      </Router></DatalogsProvider></ChannelsProvider></LayoutProvider></ThemeProvider>
    );
  }
}

export default App;
