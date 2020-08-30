import { BUFFER_LENGTH } from '../util/constants.js';

function sampleRingBuffer(ringBuffer, startIndex, sampleIndex) {
    if (sampleIndex < 0.0) {
        return ringBuffer[startIndex];
    } else if (sampleIndex >= ringBuffer.length - 1) {
        if (startIndex > 0) {
            return ringBuffer[startIndex - 1];
        } else {
            return ringBuffer[ringBuffer.length - 1];
        }
    } else {
        // Performs linear interpolation between the two values closest to 
        // sampleIndex.
        let index = startIndex + ringBuffer.length + sampleIndex;
        let before = ringBuffer[Math.floor(index) % ringBuffer.length];
        let after = ringBuffer[Math.ceil(index) % ringBuffer.length];
        let mix = sampleIndex % 1.0;
        return before * (1.0 - mix) + after * mix;
    }
}

export class RealtimeBuffer {
    constructor(sampleRate) {
        this.dataBuffer = new Array(BUFFER_LENGTH);
        this.timePerSample = 1.0 / sampleRate;
        this.startTime = 0.0;
        this.startIndex = 0;
    }

    get endTime() {
        return this.startTime + BUFFER_LENGTH * this.timePerSample;
    }

    getValue(time) {
        // Convert from seconds to samples.
        let sampleIndex = Math.round((time - this.startTime) / this.timePerSample);
        return sampleRingBuffer(this.dataBuffer, this.startIndex, sampleIndex);
    }

    getMin(time) {
        let value = 1.0;
        let sampleIndex = Math.round((time - this.startTime) / this.timePerSample);
        for (let offset = -9; offset <= 9; offset++) {
            let sample = sampleRingBuffer(this.dataBuffer, this.startIndex, sampleIndex + offset);
            value = Math.min(value, sample);
        }
        return value;
    }

    getMax(time) {
        let value = 0.0;
        let sampleIndex = Math.round((time - this.startTime) / this.timePerSample);
        for (let offset = -9; offset <= 9; offset++) {
            let sample = sampleRingBuffer(this.dataBuffer, this.startIndex, sampleIndex + offset);
            value = Math.max(value, sample);
        }
        return value;
    }

    appendData(dataArray) {
        if (dataArray.length === 0) return;
        if (dataArray.length > BUFFER_LENGTH) {
            throw new Error('Cannot write more than a buffer length\'s worth of data at a time.');
        }
        let endInsertionBefore = this.startIndex + dataArray.length;
        if (endInsertionBefore <= BUFFER_LENGTH) {
            for (let index = 0; index < dataArray.length; index++) {
                this.dataBuffer[this.startIndex + index] = dataArray[index];
            }
        } else { // We need to write in two chunks.
            // Write data until the end of the buffer.
            let numItemsRemaining = BUFFER_LENGTH - this.startIndex;
            for (let index = 0; index < numItemsRemaining; index++) {
                this.databuffer[this.startIndex + index] = dataArray[index];
            }
            // Loop back around and write the rest of the data to the beginning.
            for (let index = numItemsRemaining; index < dataArray.length; index++) {
                this.databuffer[index - numItemsRemaining] = dataArray[index];
            }
        }
        // Now that we've added data to the end, the start should be placed right after the
        // end to make the ring buffer valid again.
        this.startIndex = (this.startIndex + dataArray.length) % BUFFER_LENGTH;
        this.startTime += dataArray.length * this.timePerSample;
    }

    // Generates a wiggly waveform that we can use to test gui stuff.
    fillWithTestData() {
        let sample = 0.0; // Range from -1 to 1.
        for (let i = 0; i < BUFFER_LENGTH; i++) {
            let delta = 2.0 * Math.random() - 1.0; // Range from 1.0 to -1.0
            // If the sample is already high, skew the delta so it goes lower.
            delta -= sample; // If sample is max, delta will only decrease.
            delta *= 0.09; // Only change a bit during each step.
            sample += delta;
            // Convert from -1 to 1 to 0 to 1
            this.dataBuffer[i] = (sample + 1.0) / 2.0;
        }
    }
}

export class DatalogBuffer {
    constructor(datalogInfo) {
        this.sampleRate = (1000 * 1000) / datalogInfo.cycle_time_us;
        this.numLods = datalogInfo.total_num_lods;
        this.lodSampleInterval = datalogInfo.lod_sample_interval;
        this.duration = datalogInfo.duration;

        this.buffers = [];
        let timePerSample = 1.0 / this.sampleRate;
        for (let lod = 0; lod < this.numLods; lod++) {
            this.buffers.push({
                data: new Array(BUFFER_LENGTH),
                ringStartIndex: 0,
                timePerSample,
            });
            timePerSample *= this.lodSampleInterval;
        }
    }

    // Returns the index of an LOD which uses just over this amount of time per sample.
    getBestLod(timePerSample) {
        for (let lod = 0; lod < this.numLods; lod++) {
            if (this.buffers[lod].timePerSample > timePerSample) {
                return lod;
            }
        }
        return this.numLods - 1;
    }

    getValue(time, lod) {
        let buffer = this.buffers[lod];
        let sampleIndex = time / buffer.timePerSample;
        return sampleRingBuffer(buffer.data, buffer.ringStartIndex, sampleIndex);
    }
}