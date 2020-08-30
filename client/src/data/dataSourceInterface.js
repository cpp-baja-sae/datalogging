import realtimeBufferStore from '../data/realtimeBufferStore.js';
import DatalogBufferStore from './DatalogBufferStore.js';

const REALTIME_SOURCE = 'REALTIME';
const LOGGED_SOURCE = 1;

class DataSourceAbstractor {
  constructor() {
    this.listeners = [];
    this.settingsListeners = [];
    this.zoomMagnitude = 0;
    this.referenceTime = 0.0;
    realtimeBufferStore.addListener(() => {
      if (this.sourceIsRealtime()) this._triggerListeners();
    });
    this.currentBufferStore = realtimeBufferStore;
  }

  sourceIsRealtime() {
    return this.currentBufferStore === realtimeBufferStore;
  }

  useDatalogSource(datalogInfo) {
    this.currentBufferStore = new DatalogBufferStore(datalogInfo);
  }

  useRealtimeSource() {
    this.currentBufferStore = realtimeBufferStore;
  }

  getValue(channel, time) {
    if (this.sourceIsRealtime()) {
      return realtimeBufferStore.getValue(channel, time);
    } else {
      return this.currentBufferStore.getValue(channel, time, this.getTimePerPixel());
    }
  }

  getMin(channel, time) {
    if (this.sourceIsRealtime())
      return realtimeBufferStore.getMin(channel, time);
    else
      return 0;
  }

  getMax(channel, time) {
    if (this.sourceIsRealtime())
      return realtimeBufferStore.getMax(channel, time);
    else
      return 0;
  }

  addListener(callback) {
    this.listeners.push(callback);
  }

  removeListener(callbackToRemove) {
    this.listeners = this.listeners.filter(item => item !== callbackToRemove);
  }

  _triggerListeners() {
    for (let listener of this.listeners) {
      listener();
    }
  }

  increaseZoom() {
    this.zoomMagnitude += 1;
    console.log(this.zoomMagnitude);
    this._triggerSettingsListeners();
  }

  decreaseZoom() {
    this.zoomMagnitude -= 1;
    this._triggerSettingsListeners();
  }

  getZoomStrength() {
    return Math.pow(2.0, this.zoomMagnitude);
  }

  getZoomStrengthText() {
    if (this.zoomMagnitude < 0) {
      return "1/" + (1 << -this.zoomMagnitude) + "x";
    } else {
      return "" + (1 << this.zoomMagnitude) + "x";
    }
  }

  setViewPosition(newTime) {
    this.referenceTime = newTime;
    if (this.sourceIsRealtime()) {
      this.referenceTime = Math.min(0.0, this.referenceTime);
    } else {
      this.referenceTime = Math.max(0.0, this.referenceTime);
    }
    this._triggerSettingsListeners();
  }

  getViewPosition() {
    return this.referenceTime;
  }

  getViewPositionText() {
    let abs = Math.abs(this.referenceTime)
    return (this.sourceIsRealtime() ? 'T-' : 'T+')
      + (abs / 3600).toFixed(0)
      + ":"
      + (abs / 60).toFixed(0).padStart(2, '0')
      + ":"
      + abs.toFixed(1).padStart(4, '0');
  }

  getTimePerPixel() {
    return 0.005 / this.getZoomStrength();
  }

  addSettingsListener(callback) {
    this.settingsListeners.push(callback);
  }

  removeSettingsListener(callbackToRemove) {
    this.settingsListeners = this.settingsListeners.filter(item => item !== callbackToRemove);
  }

  _triggerSettingsListeners() {
    this._triggerListeners();
    for (let listener of this.settingsListeners) {
      listener();
    }
  }
}

const instance = new DataSourceAbstractor();

export default instance;
