import { FrameBuffer, LowResFrameBuffer } from './frame';
import { addStreamListener, getDefaultFormat } from '../util/backend.js';
import { BUFFER_LENGTH } from '../util/constants.js';

class RealtimeSource {
  constructor(dataFormat) {
    this.listeners = [];
    this.buffer = new FrameBuffer(dataFormat);
    this.bufferEnd = 0;
    this.sampleRate = (1000 * 1000) / dataFormat.frame_time_us;
    this.format = dataFormat;
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

class DatalogSource {
  constructor(datalogInfo) {
    this.listeners = [];
    this.sampleRate = (1000 * 1000) / datalogInfo.frame_time_us;
    this.format = datalogInfo;
    this.buffers = [{
      buffer: new FrameBuffer(datalogInfo),
      sampleRate: this.sampleRate,
      startIndex: -1,
      currentlyFetching: false,
      queuedFetch: null
    }];
    let lodSampleRate = this.sampleRate;
    for (let lod = 1; lod < datalogInfo.total_num_lods; lod++) {
      lodSampleRate /= datalogInfo.lod_sample_interval;
      this.buffers.push({
        buffer: new LowResFrameBuffer(datalogInfo),
        sampleRate: lodSampleRate,
        startIndex: -1,
        currentlyFetching: false,
        queuedFetch: null
      });
    }
  }

  // Point is a positive number.
  getValue(point, channel) {
    let [lod, index] = this._pointToBufferIndex(point);
    if (
      index < this.buffers[lod].startIndex 
      || index >= (this.buffers[lod].startIndex + BUFFER_LENGTH) 
      || index < 0
    ) {
      return 0;
    } else {
      return this.buffers[lod].buffer.getValue(index % BUFFER_LENGTH, channel);
    }
  }

  // Point is a positive number.
  getMin(point, channel) {
    let [lod, index] = this._pointToBufferIndex(point);
    if (
      index < this.buffers[lod].startIndex 
      || index >= (this.buffers[lod].startIndex + BUFFER_LENGTH) 
      || index < 0
    ) {
      return 0;
    } else {
      return this.buffers[lod].buffer.getMin(index % BUFFER_LENGTH, channel);
    }
  }

  // Point is a positive number.
  getMax(point, channel) {
    let [lod, index] = this._pointToBufferIndex(point);
    if (
      index < this.buffers[lod].startIndex 
      || index >= (this.buffers[lod].startIndex + BUFFER_LENGTH) 
      || index < 0
    ) {
      return 0;
    } else {
      return this.buffers[lod].buffer.getMax(index % BUFFER_LENGTH, channel);
    }
  }

  addListener(callback) {
    this.listeners.push(callback);
  }

  removeListener(callbackToRemove) {
    this.listeners = this.listeners.filter(item => item !== callbackToRemove);
  }

  // Submits a request to retrieve data such that the start of the specified LOD
  // is at the specified index.
  _submitFetchRequest(lod, newStartIndex) {
    if (newStartIndex < 0) newStartIndex = 0;
    if (this.buffers[lod].currentlyFetching) {
      this.buffers[lod].queuedFetch = newStartIndex;
    } else {
      this.buffers[lod].currentlyFetching = true;
      (async () => {
        this.buffers[lod].currentlyFetching = false;
      })();
    }
  }

  _triggerListeners() {
    for (let listener of this.listeners) {
      listener();
    }
  }

  _selectLodForResolution() {
    let samplesPerPixel = dataInterface.getTimePerPixel() * this.sampleRate;
    let lod = 0;
    // Pick an LOD which does not have more than 1 sample per pixel.
    while (samplesPerPixel > 1.0) {
      samplesPerPixel /= this.format.lod_sample_interval;
      lod += 1;
    }
    return lod;
  }

  _pointToBufferIndex(time) {
    let lod = this._selectLodForResolution();
    let index = Math.round(time * this.buffers[lod].sampleRate);
    return [lod, index];
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
      format: {
        frame_time_us: 0,
        layout: []
      }
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

  getFormat() {
    return this.currentSource.format;
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

const dataInterface = new DataInterface();

export default dataInterface;

(async () => {
  console.error('Connecting realtime data...');
  dataInterface.realtimeSource = new RealtimeSource(await getDefaultFormat());
  dataInterface.currentSource = dataInterface.realtimeSource;
  dataInterface.realtimeSource.addListener(() => {
    if (dataInterface.isSourceRealtime()) dataInterface._triggerListeners();
  });
  console.error('Complete!');
})();
