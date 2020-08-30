import React from 'react';

import styles from './ColorPicker.module.css';
import { COLORS } from '../util/constants';

export default class ColorPicker extends React.Component {
  render() {
    let swatches = [];
    for (let index = 0; index < COLORS.length; index++) {
      let color = COLORS[index];
      let selectedClass = index === this.props.value ? styles.selected : '';
      swatches.push((<div 
        className={styles.swatch + ' ' + selectedClass}
        style={{background: color}}
        key={index}
        onClick={_ => this.props.onChange(index)}
      />));
    }
    return (<div className={styles.root}>{swatches}</div>)
  }
}