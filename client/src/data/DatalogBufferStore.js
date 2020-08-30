import { DatalogBuffer } from './buffers';

class DatalogBufferStore {
    constructor(datalogInfo) {
        this.listeners = [];
        this.buffers = [];
        let total_channels = datalogInfo.num_adcs * datalogInfo.num_channels;
        for (let channel = 0; channel < total_channels; channel++) {
            let buffer = new DatalogBuffer(datalogInfo);
            this.buffers.push(buffer);
        }
    }

    // Point is a time from after the datalog was first captured. 3.0 would get the value 3 seconds
    // after the datalog started. timePerPixel is the amount of seconds that elapses per pixel on
    // the graph this data will be drawn on. It is used to pick an appropriate LOD whose data has
    // just over that amount of time per sample.
    getValue(channel, point, timePerPixel) {
        const buffer = this.buffers[channel];
        const lod = buffer.getBestLod(timePerPixel);
        return buffer.getValue(buffer.endTime + point, lod);
    }

    getMin(channel, point, lod) {
        return 0;
    }

    getMax(channel, point, lod) {
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
}

export default DatalogBufferStore;