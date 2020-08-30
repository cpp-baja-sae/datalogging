import ArrowDropDown from '@material-ui/icons/ArrowDropDown';
import ArrowDropUp from '@material-ui/icons/ArrowDropUp';
import Delete from '@material-ui/icons/Cancel';
import IconButton from '@material-ui/core/IconButton';
import MenuItem from '@material-ui/core/MenuItem';
import React from 'react';
import TextField from '@material-ui/core/TextField';

import Graph from './Graph.js';
import styles from './GraphRow.module.css';
import { NUM_ADCS, CHANNELS_PER_ADC, COLORS, NUM_CHANNELS } from '../util/constants.js';
import ChannelSettings from './ChannelSettings.js';
import ColorPicker from './ColorPicker';
import { LayoutConsumer } from '../state/Layout.js';
import { ChannelsConsumer } from '../state/Channels.js';

class GraphRow extends React.Component {
  constructor(props) {
    super(props);

    window.expand = () => {
      this.setState({ expanded: true });
    }

    this.state = {
      expanded: false,
    };
  }

  toggleExpanded() {
    this.setState((state) => {
      return {
        expanded: !state.expanded
      };
    });
  }

  patchSettings(patch) {
    let settings = this.props.settings;
    for (let key in patch) {
      settings[key] = patch[key];
    }
    this.props.onChange(settings);
  }

  renderSettings(layout, channelStore) {
    let graphSettings = layout.graphs[this.props.index];

    let channelOptions = [];
    let sortedChannels = channelStore.channels.map((value, index) => [value, index]);
    sortedChannels.sort((a, b) => a[0].label.localeCompare(b[0].label));
    for (let channel of sortedChannels) {
      channelOptions.push((
        <MenuItem key={'' + channel[1]} value={'' + channel[1]}>{channel[0].label}</MenuItem>
      ));
    }
    let patchGraph = patch => layout.patchGraph(this.props.index, patch);

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
      <ChannelSettings index={graphSettings.channel} />
    </div>);
  }

  renderInfo(layout, channelStore) {
    let graphSettings = layout.graphs[this.props.index];
    let channelSettings = channelStore.channels[graphSettings.channel];
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

    return (<LayoutConsumer>{layout => (<ChannelsConsumer>{channelStore => {
      let graphSettings = layout.graphs[this.props.index];
      return (<div className={styles.root + expandedClass}>
        {this.state.expanded
          ? this.renderSettings(layout, channelStore)
          : this.renderInfo(layout, channelStore)}
        <Graph 
          channel={graphSettings.channel} 
          color={COLORS[graphSettings.color]} 
          showCursor={true} 
          showBounds={true}
        />
      </div>);
    }}</ChannelsConsumer>)}</LayoutConsumer>);
  }
}

export default GraphRow;