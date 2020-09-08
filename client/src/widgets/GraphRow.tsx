import ArrowDropDown from '@material-ui/icons/ArrowDropDown';
import ArrowDropUp from '@material-ui/icons/ArrowDropUp';
import Delete from '@material-ui/icons/Cancel';
import IconButton from '@material-ui/core/IconButton';
import MenuItem from '@material-ui/core/MenuItem';
import React from 'react';
import TextField from '@material-ui/core/TextField';

import Graph from './Graph';
import styles from './GraphRow.module.css';
import { COLORS } from '../util/constants';
import ChannelSettingsEditor from './ChannelSettings';
import ColorPicker from './ColorPicker';
import { LayoutConsumer, LayoutState, GraphSettings } from '../state/Layout';
import dataInterface from '../data/dataInterface';

type GraphRowProps = {
  index: number,
};
type GraphRowState = {
  expanded: boolean
};

class GraphRow extends React.Component<GraphRowProps, GraphRowState> {
  listener: () => void;

  constructor(props: Readonly<GraphRowProps>) {
    super(props);
    this.listener = () => this.forceUpdate();

    this.state = {
      expanded: false,
    };
  }

  componentDidMount() {
    dataInterface.addSettingsListener(this.listener);
  }

  componentWillUnmount() {
    dataInterface.removeSettingsListener(this.listener);
  }

  toggleExpanded() {
    this.setState((state) => {
      return {
        expanded: !state.expanded
      };
    });
  }

  renderSettings(layout: LayoutState) {
    let graphSettings = layout.graphs[this.props.index];

    let channelOptions = [];
    let sortedChannels = layout.channelSettings.map((value, index) => { return { value, index }; });
    sortedChannels.sort((a, b) => a.value.label.localeCompare(b.value.label));
    for (let channel of sortedChannels) {
      channelOptions.push((
        <MenuItem key={'' + channel.index} value={'' + channel.index}>{channel.value.label}</MenuItem>
      ));
    }
    let patchGraph = (patch: Partial<GraphSettings>) => layout.patchGraph(this.props.index, patch);

    return (<div className={styles.settings}>
      <div className={styles.header}>
        <div className={styles.infoHeader}>Graph Settings</div>
        <span>
          <IconButton size="small" onClick={_ => layout.deleteGraph(graphSettings.key)}>
            <Delete />
          </IconButton>
          <IconButton size="small" onClick={this.toggleExpanded.bind(this)}>
            <ArrowDropUp />
          </IconButton>
        </span>
      </div>
      <form noValidate autoComplete="off" className={styles.channelSelect}>
        <TextField
          select
          type="number"
          id="channel"
          label="Channel"
          variant="outlined"
          value={graphSettings.channel}
          onChange={event => patchGraph({
            channel: parseInt(event.target.value)
          })}
        >
          {channelOptions}
        </TextField>
      </form>
      <ColorPicker value={graphSettings.color} onChange={color => patchGraph({ color: color })} />
      <div className={styles.divider}>Channel Settings</div>
      <ChannelSettingsEditor index={graphSettings.channel} />
    </div>);
  }

  renderInfo(layout: LayoutState) {
    let graphSettings = layout.graphs[this.props.index];
    let channelSettings = layout.channelSettings[graphSettings.channel];
    return (<div className={styles.info}>
      <div className={styles.header}>
        <div className={styles.displayName}>{channelSettings.label}</div>
        <IconButton size="small" edge="end" onClick={this.toggleExpanded.bind(this)}>
          <ArrowDropDown />
        </IconButton>
      </div>
    </div>);
  }

  render() {
    let expandedClass = this.state.expanded ? ` ${styles.expanded}` : '';

    return (<LayoutConsumer>{layoutIn => {
      let layout = layoutIn as LayoutState;
      let graphSettings = layout.graphs[this.props.index];
      return (<div className={styles.root + expandedClass}>
        {this.state.expanded
          ? this.renderSettings(layout)
          : this.renderInfo(layout)}
        <Graph
          channel={graphSettings.channel}
          color={COLORS[graphSettings.color]}
          showCursor={true}
          showBounds={true}
        />
      </div>);
    }}</LayoutConsumer>);
  }
}

export default GraphRow;