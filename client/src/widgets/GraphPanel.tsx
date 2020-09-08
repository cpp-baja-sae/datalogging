import React from 'react';
import Button from '@material-ui/core/Button';

import styles from './GraphPanel.module.css';

import GraphRow from './GraphRow';
import { LayoutConsumer, LayoutState } from '../state/Layout';
import ValueTooltip from './ValueTooltip';

class GraphPanel extends React.Component {
  render() {
    return (<div className={styles.root}>
      <LayoutConsumer>{layoutIn => {
        let layout = layoutIn as LayoutState;
        let graphWidgets = [];
        for (let index = 0; index < layout.graphs.length; index++) {
          let key = layout.graphs[index].key;
          graphWidgets.push(
            <GraphRow key={key} index={index} />
          );
        }
        graphWidgets.push(<div key="addGraph" className={styles.addGraph}>
          <Button variant="outlined" onClick={_ => layout.newGraph()}>Add Graph</Button>
        </div>)
        graphWidgets.push(<ValueTooltip key="tooltip" />)
        return graphWidgets;
      }}</LayoutConsumer>
    </div>);
  }
}

export default GraphPanel;
