import { FrameBuffer, LowResFrameBuffer, GenericFrameBuffer } from './frame';
import { addStreamListener, settings, readDataSpan } from '../util/backend';
import { BUFFER_LENGTH } from '../util/constants';
import { DataFormat, DatalogInfo } from './types';
import { formatDate } from '../util/misc';

interface DataSource {
  getValue: (point: number, channel: number) => any;
  getMin: (point: number, channel: number) => any;
  getMax: (point: number, channel: number) => any;
  onWindowChange: (newZoom: number, newBaseTime: number) => void;
  format: DataFormat;
  description: string;
}

class RealtimeSource implements DataSource {
  listeners: Array<() => void>;
  buffer: FrameBuffer;
  bufferEnd: number;
  sampleRate: number;
  format: DataFormat;
  lod: number;
  scale: number; // Based on lod.
  description = 'REALTIME';

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

  onWindowChange(_newZoom: number, _newBaseTime: number) { }

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
    futureStartIndex: number,
    currentlyFetching: boolean,
    queuedFetch: DatalogFetchRequest | null,
  }>;
  sampleRate: number;
  format: DatalogInfo;
  description: string;

  constructor(datalogInfo: DatalogInfo) {
    this.listeners = [];
    this.sampleRate = (1000 * 1000) / datalogInfo.frame_time_us;
    this.format = datalogInfo;
    this.description = formatDate(datalogInfo.jsdate);
    this.buffers = [{
      buffer: new FrameBuffer(datalogInfo),
      sampleRate: this.sampleRate,
      startIndex: -1,
      futureStartIndex: -1,
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
        futureStartIndex: -1,
        currentlyFetching: false,
        queuedFetch: null
      });
    }
    for (let lod = 0; lod < datalogInfo.total_num_lods; lod++) {
      this._submitFetchRequest(lod, 0);
    }
  }

  // Point is a positive number.
  getValue(point: number, channel: number) {
    let [lod, index] = this._pointToBufferIndex(point);
    if (
      index < this.buffers[lod].startIndex
      || index >= (this.buffers[lod].startIndex + BUFFER_LENGTH)
      || index < 0
      || this.buffers[lod].startIndex === -1 // Nothing has been retrieved yet.
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
      || this.buffers[lod].startIndex === -1 // Nothing has been retrieved yet.
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
      || this.buffers[lod].startIndex === -1 // Nothing has been retrieved yet.
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

  onWindowChange(_newZoom: number, newBaseTime: number) {
    let [newLod, index] = this._pointToBufferIndex(newBaseTime);
    let newBaseIndex = index - BUFFER_LENGTH / 4;
    if (Math.abs(this.buffers[newLod].futureStartIndex - newBaseIndex) > BUFFER_LENGTH / 4) {
      this._submitFetchRequest(newLod, newBaseIndex);
    }
  }

  // Submits a request to retrieve data such that the start of the specified LOD
  // is at the specified index.
  _submitFetchRequest(lod: number, newStartIndex: number) {
    if (newStartIndex < 0) newStartIndex = 0;
    this.buffers[lod].futureStartIndex = newStartIndex;
    if (this.buffers[lod].currentlyFetching) {
      this.buffers[lod].queuedFetch = newStartIndex;
    } else {
      this.buffers[lod].currentlyFetching = true;
      (async () => {
        let data = await readDataSpan(
          this.format.date,
          newStartIndex,
          newStartIndex + BUFFER_LENGTH,
          lod
        );
        let buffer = this.buffers[lod].buffer;
        // The efficiency of this can and should be improved. We don't always
        // need to retrieve an entire buffer's worth of data, sometimes we
        // already have a portion of it.
        for (let i = 0; i < BUFFER_LENGTH; i++) {
          buffer.storeRawFrame(
            (i + newStartIndex) % BUFFER_LENGTH,
            data,
            i * buffer.frameLength
          );
        }
        this.buffers[lod].startIndex = newStartIndex;
        this._triggerListeners();
        let queuedFetch = this.buffers[lod].queuedFetch;
        this.buffers[lod].currentlyFetching = false;
        if (queuedFetch !== null) {
          this.buffers[lod].queuedFetch = null;
          this._submitFetchRequest(lod, queuedFetch);
        }
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
      if (lod === this.format.total_num_lods) return lod - 1;
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
      onWindowChange: (_1, _2_) => 0,
      format: {
        version: 1,
        frame_time_us: 0,
        total_num_lods: 0,
        lod_sample_interval: 4,
        layout: []
      },
      description: 'LOADING...'
    };

    this.realtimeSource = dummySource;
    this.currentSource = dummySource;
  }

  isSourceRealtime() {
    return this.currentSource === this.realtimeSource;
  }

  useDatalogSource(datalogInfo: DatalogInfo) {
    let datalogSource = new DatalogSource(datalogInfo);
    datalogSource.addListener(() => this._triggerListeners());
    this.currentSource = datalogSource;
    this.referenceTime = 0.0;
    this._triggerSettingsListeners();
  }

  useRealtimeSource() {
    this.currentSource = this.realtimeSource;
    this.referenceTime = 0.0;
    this._triggerSettingsListeners();
  }

  getFormat() {
    return this.currentSource.format;
  }

  getSourceDescription() {
    return this.currentSource.description;
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
    return 0.1 / this.getZoomStrength();
  }

  addSettingsListener(callback: () => void) {
    this.settingsListeners.push(callback);
  }

  removeSettingsListener(callbackToRemove: () => void) {
    this.settingsListeners = this.settingsListeners.filter(item => item !== callbackToRemove);
  }

  _triggerSettingsListeners() {
    this._triggerListeners();
    this.currentSource.onWindowChange(this.getZoomStrength(), this.referenceTime);
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
  dataInterface._triggerSettingsListeners();
  realtimeSource.addListener(() => {
    if (dataInterface.isSourceRealtime()) dataInterface._triggerListeners();
  });
  console.error('Complete!');
})();
