import React from 'react';
import Button from '@material-ui/core/Button/Button';
import { Link } from 'react-router-dom';
import FolderIcon from '@material-ui/icons/Folder';
import SaveIcon from '@material-ui/icons/Save';
import FileCopyIcon from '@material-ui/icons/FileCopy';
import ZoomInIcon from '@material-ui/icons/Add';
import ZoomOutIcon from '@material-ui/icons/Remove';
import CodeIcon from '@material-ui/icons/Code';
import EditIcon from '@material-ui/icons/Edit';

import dataSourceInterface from '../data/dataSourceInterface';

import styles from './Header.module.css';

class Header extends React.Component {
  componentDidMount() {
    this.listener = () => this.forceUpdate();
    dataSourceInterface.addSettingsListener(this.listener);
  }

  componentWillUnmount() {
    dataSourceInterface.removeSettingsListener(this.listener);
  }

  render() {
    let zoomStrengthText = dataSourceInterface.getZoomStrengthText();

    let dragTimeOnClick = event => {
      let element = event.target;
      element.setPointerCapture(event.pointerId);
      element.style.cursor = "col-resize";
      let x = event.x;
      element.onpointermove = event => {
        let dx = event.x - x;
        x = event.x;
        if (isNaN(dx)) return; // I don't understand how javascript works.
        let dt = dx * dataSourceInterface.getTimePerPixel() * 4.0;
        let newTime = dataSourceInterface.getViewPosition() + dt;
        dataSourceInterface.setViewPosition(newTime);
      };
      element.onpointerup = event => {
        element.onpointermove = null;
        element.releasePointerCapture(event.pointerId);
        element.style.cursor = undefined;
      };
    };

    return (
      <div className={styles.header}>
        <span>
          <span className={[styles.weak, styles.c1].join(" ")}>data source:</span>
          <span className={[styles.strong, styles.c2].join(" ")}>REALTIME</span>
          <span
            className={[styles.strong, styles.c3, styles.canInteract, styles.padLeft, styles.padRight].join(" ")}
            title="Select Data Source"
          >
            <Link to="/pickDataSource"><FolderIcon className={styles.icon} /></Link>
          </span>
        </span>
        <span>
          <span className={[styles.weak, styles.c1].join(" ")}>current layout:</span>
          <span className={[styles.strong, styles.c2].join(" ")}>DEFAULT</span>
          <span
            className={[styles.strong, styles.c3, styles.canInteract, styles.padLeft].join(" ")}
            title="Save Current Layout"
          >
            <SaveIcon className={styles.icon} />
          </span>
          <span
            className={[styles.strong, styles.c4, styles.canInteract].join(" ")}
            title="Save As New Layout"
          >
            <FileCopyIcon className={styles.icon} />
          </span>
          <span
            className={[styles.strong, styles.c5, styles.canInteract, styles.padRight].join(" ")}
            title="Select Layout"
          >
            <Link to="/pickLayout"><FolderIcon className={styles.icon} /></Link>
          </span>
        </span>
        <Link to="/graphs" title="Go To Graphs Page">
          <span className={[styles.link, styles.c1, styles.canInteract].join(" ")}>
            GRAPHS
                </span>
        </Link>
        <Link to="/channels" title="Go To Channel List">
          <span className={[styles.link, styles.c1, styles.canInteract].join(" ")}>
            CHANNELS
                </span>
        </Link>
        <Link to="/settings" title="Go To Settings Page">
          <span className={[styles.link, styles.c1, styles.canInteract].join(" ")}>
            SETTINGS
                </span>
        </Link>
        <span>
          <span className={[styles.weak, styles.c1].join(" ")}>zoom:</span>
          <span className={[styles.strong, styles.c2].join(" ")}>{zoomStrengthText}</span>
          <span
            className={[styles.strong, styles.c3, styles.canInteract, styles.padLeft].join(" ")}
            title="Zoom In"
            onClick={() => dataSourceInterface.increaseZoom()}
          >
            <ZoomInIcon className={styles.icon} />
          </span>
          <span
            className={[styles.strong, styles.c4, styles.canInteract, styles.padRight].join(" ")}
            title="Zoom Out"
            onClick={() => dataSourceInterface.decreaseZoom()}
          >
            <ZoomOutIcon className={styles.icon} />
          </span>
        </span>
        <span>
          <span className={[styles.weak, styles.c1].join(" ")}>view position:</span>
          <span className={[styles.strong, styles.c2].join(" ")}>
            {dataSourceInterface.getViewPositionText()}
          </span>
          <span
            className={[styles.strong, styles.c3, styles.canInteract, styles.padLeft].join(" ")}
            title="Type In A New Value"
          >
            <EditIcon className={styles.icon} />
          </span>
          <span
            className={[styles.strong, styles.c4, styles.canInteract, styles.padRight].join(" ")}
            title="Click And Drag To Change Current Time"
            onPointerDown={dragTimeOnClick}
          >
            <CodeIcon className={styles.icon} />
          </span>
        </span>
      </div>
    );
  }
}

export default Header;