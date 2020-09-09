import { FrameBuffer, LowResFrameBuffer, GenericFrameBuffer } from './frame';
import { addStreamListener, settings } from '../util/backend';
import { BUFFER_LENGTH } from '../util/constants';
import { DataFormat, DatalogInfo } from './types';

interface DataSource {
  getValue: (point: number, channel: number) => any;
  getMin: (point: number, channel: number) => any;
  getMax: (point: number, channel: number) => any;
  format: DataFormat;
}

class RealtimeSource implements DataSource {
  listeners: Array<() => void>;
  buffer: FrameBuffer;
  bufferEnd: number;
  sampleRate: number;
  format: DataFormat;
  lod: number;
  scale: number; // Based on lod.

  constructor(dataFormat: DataFormat, lod: number) {
    this.listeners = [];
    this.lod = lod;
    this.scale = Math.pow(dataFormat.lod_sample_interval, this.lod);
    this.bufferEnd = 0;
    this.sampleRate = (1000 * 1000) / dataFormat.frame_time_us;
    this.format = dataFormat;
    if (this.lod === 0) {
      this.buffer = new FrameBuffer(this.format);
    } else {
      this.buffer = new LowResFrameBuffer(this.format);
    }
    addStreamListener((newData) => {
      this.buffer.storeRawFrame(this.bufferEnd % BUFFER_LENGTH, newData);
      this.bufferEnd += 1;
      this._triggerListeners();
    });
    settings.stream_lod.subscribe((newLod) => {
      this.changeLod(newLod);
    });
  }

  changeLod(lod: number) {
    if (lod === this.lod) return;
    this.lod = lod;
    this.scale = Math.pow(this.format.lod_sample_interval, this.lod);
    this._makeBuffers();
  }

  _makeBuffers() {
    if (this.lod === 0) {
      this.buffer = new FrameBuffer(this.format);
    } else {
      this.buffer = new LowResFrameBuffer(this.format);
    }
    this.bufferEnd = 0;
  }

  // Point is a negative number. Zero is most recent sample, negative values are from times
  // before that point.
  getValue(point: number, channel: number) {
    let index = this._pointToBufferIndex(point);
    if (index < 0) return 0;
    return this.buffer.getValue(index, channel);
  }

  getMin(point: number, channel: number) {
    let index = this._pointToBufferIndex(point);
    if (index < 0) return 0;
    return this.buffer.getMin(index, channel);
  }

  getMax(point: number, channel: number) {
    let index = this._pointToBufferIndex(point);
    if (index < 0) return 0;
    return this.buffer.getMax(index, channel);
  }

  addListener(callback: () => void) {
    this.listeners.push(callback);
  }

  removeListener(callbackToRemove: () => void) {
    this.listeners = this.listeners.filter(item => item !== callbackToRemove);
  }

  _triggerListeners() {
    for (let listener of this.listeners) {
      listener();
    }
  }

  _pointToBufferIndex(point: number) {
    if (point > 0) return (this.bufferEnd - 1) % BUFFER_LENGTH;
    return (this.bufferEnd - 1 + Math.round(point * this.sampleRate / this.scale)) % BUFFER_LENGTH;
  }
}

type DatalogFetchRequest = number;

class DatalogSource implements DataSource {
  listeners: Array<() => void>;
  buffers: Array<{
    buffer: GenericFrameBuffer,
    sampleRate: number,
    startIndex: number,
    currentlyFetching: boolean,
    queuedFetch: DatalogFetchRequest | null,
  }>;
  sampleRate: number;
  format: DataFormat;

  constructor(datalogInfo: DatalogInfo) {
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
  getValue(point: number, channel: number) {
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
  getMin(point: number, channel: number) {
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
  getMax(point: number, channel: number) {
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

  addListener(callback: () => void) {
    this.listeners.push(callback);
  }

  removeListener(callbackToRemove: () => void) {
    this.listeners = this.listeners.filter(item => item !== callbackToRemove);
  }

  // Submits a request to retrieve data such that the start of the specified LOD
  // is at the specified index.
  _submitFetchRequest(lod: number, newStartIndex: number) {
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

  _pointToBufferIndex(time: number) {
    let lod = this._selectLodForResolution();
    let index = Math.round(time * this.buffers[lod].sampleRate);
    return [lod, index];
  }
}

class DataInterface {
  listeners: Array<() => void>;
  settingsListeners: Array<() => void>;
  zoomMagnitude: number;
  referenceTime: number;
  realtimeSource: DataSource;
  currentSource: DataSource;

  constructor() {
    this.listeners = [];
    this.settingsListeners = [];
    this.zoomMagnitude = 0;
    this.referenceTime = 0.0;

    // This is used until the *actual* realtime source is loaded.
    const dummySource: DataSource = {
      getValue: (_1, _2) => 0,
      getMin: (_1, _2) => 0,
      getMax: (_1, _2) => 0,
      format: {
        version: 1,
        frame_time_us: 0,
        total_num_lods: 0,
        lod_sample_interval: 4,
        layout: []
      }
    };

    this.realtimeSource = dummySource;
    this.currentSource = dummySource;
  }

  isSourceRealtime() {
    return this.currentSource === this.realtimeSource;
  }

  useDatalogSource(datalogInfo: DatalogInfo) {
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
  getValue(time: number, channel: number) {
    return this.currentSource.getValue(time, channel);
  }

  getMin(time: number, channel: number) {
    return this.currentSource.getMin(time, channel);
  }

  getMax(time: number, channel: number) {
    return this.currentSource.getMax(time, channel);
  }

  addListener(callback: () => void) {
    this.listeners.push(callback);
  }

  removeListener(callbackToRemove: () => void) {
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

  setViewPosition(newTime: number) {
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
      + Math.floor(abs / 3600).toFixed(0)
      + ":"
      + Math.floor((abs / 60) % 60).toFixed(0).padStart(2, '0')
      + ":"
      + (abs % 60).toFixed(1).padStart(4, '0');
  }

  getTimePerPixel() {
    return 0.005 / this.getZoomStrength();
  }

  addSettingsListener(callback: () => void) {
    this.settingsListeners.push(callback);
  }

  removeSettingsListener(callbackToRemove: () => void) {
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
  let format = await settings.default_format.getOnce();
  let lod = await settings.stream_lod.getOnce();
  let realtimeSource = new RealtimeSource(format, lod);
  dataInterface.realtimeSource = realtimeSource;
  dataInterface.currentSource = dataInterface.realtimeSource;
  realtimeSource.addListener(() => {
    if (dataInterface.isSourceRealtime()) dataInterface._triggerListeners();
  });
  console.error('Complete!');
})();
