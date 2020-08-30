import { RealtimeBuffer } from './buffers';
import { addStreamListener } from '../util/backend.js';
import { NUM_CHANNELS } from '../util/constants.js';

class RealtimeBufferStore {
    constructor() {
        this.listeners = [];
        this.buffers = [];
        for (let channel = 0; channel < NUM_CHANNELS; channel++) {
            let buffer = new RealtimeBuffer(100.0);
            buffer.fillWithTestData();
            this.buffers.push(buffer);
        }
        addStreamListener((newData) => {
            for (let channel = 0; channel < NUM_CHANNELS; channel++) {
                this.buffers[channel].appendData(newData[channel]);
            }
            this._triggerListeners();
        });
    }

    // Point is a negative number. Zero is most recent sample, negative values are from times
    // before that point.
    getValue(channel, point) {
        let buffer = this.buffers[channel];
        return buffer.getValue(buffer.endTime + point);
    }

    getMin(channel, point) {
        let buffer = this.buffers[channel];
        return buffer.getMin(buffer.endTime + point);
    }

    getMax(channel, point) {
        let buffer = this.buffers[channel];
        return buffer.getMax(buffer.endTime + point);
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

let instance = new RealtimeBufferStore();

export default instance;