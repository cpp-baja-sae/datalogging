import React from 'react';
import Button from '@material-ui/core/Button';

import styles from './GraphPanel.module.css';

import GraphRow from './GraphRow.js';
import { LayoutConsumer } from '../state/Layout';
import ValueTooltip from './ValueTooltip';

class GraphPanel extends React.Component {
  render() {
    return (<div className={styles.root}>
      <LayoutConsumer>{layout => {
        let graphWidgets = [];
        for (let index in layout.graphs) {
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
