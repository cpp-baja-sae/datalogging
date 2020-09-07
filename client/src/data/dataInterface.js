import { FrameBuffer } from './frame';
import { addStreamListener, getDefaultFormat } from '../util/backend.js';
import { BUFFER_LENGTH } from '../util/constants.js';

class RealtimeSource {
  constructor(dataFormat) {
    this.listeners = [];
    this.buffer = new FrameBuffer(dataFormat);
    this.bufferEnd = 0;
    this.sampleRate = (1000 * 1000) / dataFormat.frame_time_us;
    addStreamListener((newData) => {
      this.buffer.storeRawFrame(this.bufferEnd % BUFFER_LENGTH, newData);
      this.bufferEnd += 1;
      this._triggerListeners();
    });
  }

  // Point is a negative number. Zero is most recent sample, negative values are from times
  // before that point.
  getValue(point, channel) {
    let index = this._pointToBufferIndex(point);
    if (index < 0) return 0;
    return this.buffer.getValue(index, channel);
  }

  getMin(point, channel) {
    let index = this._pointToBufferIndex(point);
    if (index < 0) return 0;
    return this.buffer.getMin(index, channel);
  }

  getMax(point, channel) {
    let index = this._pointToBufferIndex(point);
    if (index < 0) return 0;
    return this.buffer.getMax(index, channel);
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

  _pointToBufferIndex(point) {
    if (point > 0) return (this.bufferEnd - 1) % BUFFER_LENGTH;
    return (this.bufferEnd - 1 + Math.round(point * this.sampleRate)) % BUFFER_LENGTH;
  }
}

class DataInterface {
  constructor() {
    this.listeners = [];
    this.settingsListeners = [];
    this.zoomMagnitude = 0;
    this.referenceTime = 0.0;

    // This is used until the *actual* realtime source is loaded.
    const dummySource = {
      getValue: (_1, _2) => 0,
      getMin: (_1, _2) => 0,
      getMax: (_1, _2) => 0,
    };

    this.realtimeSource = dummySource;
    this.currentSource = dummySource;
  }

  isSourceRealtime() {
    return this.currentSource === this.realtimeSource;
  }

  useDatalogSource(datalogInfo) {
    throw 'Not Yet Implemented';
  }

  useRealtimeSource() {
    this.currentSource = this.realtimeSource;
  }

  // If `isSourceRealtime()`, then time is a negative value where 0 is the most
  // recent data value and anything lower than that is data received earlier. if 
  // the current source is a datalog instead, then time is a positive number
  // where 0 is the first piece of data recorded.
  getValue(time, channel) {
    return this.currentSource.getValue(time, channel);
  }

  getMin(time, channel) {
    return this.currentSource.getMin(time, channel);
  }

  getMax(time, channel) {
    return this.currentSource.getMax(time, channel);
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
    if (this.isSourceRealtime()) {
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
    return (this.isSourceRealtime() ? 'T-' : 'T+')
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

const instance = new DataInterface();

export default instance;

(async () => {
  console.error('Connecting realtime data...');
  instance.realtimeSource = new RealtimeSource(await getDefaultFormat());
  instance.currentSource = instance.realtimeSource;
  instance.realtimeSource.addListener(() => {
    if (instance.isSourceRealtime()) instance._triggerListeners();
  });
  console.error('Complete!');
})();
