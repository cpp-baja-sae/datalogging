import urllib from 'url';

import { NUM_CHANNELS, BATCH_SIZE, MAX_VALUE } from '../util/constants.js';

const PLACEHOLDER_DATA = false;

function url(endpoint, query) {
    let queryString = '';
    if (query) {
        queryString = urllib.format({ query: query });
    }
    if (process.env.NODE_ENV === 'development') {
        // If we are running the React dev server, then the API endpoints are 
        // technically hosted on another server.
        return `http://raspberrypi.local${endpoint}${queryString}`;
    } else {
        // Otherwise, it's fine to use the relative path.
        return endpoint + queryString;
    }
}

function wsUrl(endpoint) {
    if (process.env.NODE_ENV === 'development') {
        // If we are running the React dev server, then the API endpoints are 
        // technically hosted on another server.
        return `ws://raspberrypi.local${endpoint}`;
    } else {
        // Otherwise, it's fine to use the relative path.
        return `ws://${window.location.hostname}`;
    }
}

function parseBatch(batch) {
    let values = [];
    batch = new Uint8Array(batch);
    for (let valIndex = 0; valIndex < NUM_CHANNELS; valIndex++) {
        let value = (batch[valIndex * 2 + 0] << 8) + batch[valIndex * 2 + 1];
        values.push(value);
    }
    return values;
}

// Returns an array of data batches.
function parseBatches(buffer, numBatches) {
    let batches = [];
    for (let batchIndex = 0; batchIndex < numBatches; batchIndex++) {
        batches.push(parseBatch(buffer.slice(
            batchIndex * BATCH_SIZE,
            (batchIndex + 1) * BATCH_SIZE,
        )));
    }
    if (batches.length > 0) {
        // Print ADC 2, Channel 2.
        console.log(batches[0][1].toString(2));
    }
    return batches;
}

// Switches data from data[batchIndex][channelIndex] to data[channelIndex][batchIndex].
function batchwiseToChannelwiseNormalized(batchwiseData) {
    let numBatches = batchwiseData.length;
    let numChannels = batchwiseData[0].length;
    let result = [];
    for (let channel = 0; channel < numChannels; channel++) {
        let channelData = [];
        for (let batchIndex = 0; batchIndex < numBatches; batchIndex++) {
            channelData.push(batchwiseData[batchIndex][channel] / MAX_VALUE);
        }
        result.push(channelData);
    }
    return result;
}

export async function readDataSpan(date, start, end) {
    let response = await fetch(url(`/api/datalogs/${date}/span`, {
        start: start,
        end: end,
        lod: 0,
    }));
    let buffer = await response.arrayBuffer();
    return parseBatches(buffer, end - start);
}

let streamConnection = null;
let streamListeners = [];

if (PLACEHOLDER_DATA) {
    setInterval(() => {
        let dataFrame = [];
        for (let c = 0; c < NUM_CHANNELS; c++) {
            dataFrame.push([Math.random()]);
        }
        for (let listener of streamListeners) {
            listener(dataFrame);
        }
    }, 100);
}

export async function addStreamListener(listener) {
    if (streamConnection || PLACEHOLDER_DATA) {
        streamListeners.push(listener);
        return;
    }
    streamConnection = new WebSocket(wsUrl(''));
    streamConnection.onopen = () => {
        console.log('Web socket connected.');
    };
    streamListeners = [listener];
    streamConnection.onmessage = async (event) => {
        let dataBuffer = await event.data.arrayBuffer();
        let numBatches = dataBuffer.byteLength / BATCH_SIZE;
        let data = parseBatches(dataBuffer, numBatches);
        data = batchwiseToChannelwiseNormalized(data);
        for (let listener of streamListeners) {
            listener(data);
        }
    }
}

export async function disconnectStream() {
    if (!streamConnection) return;
    streamConnection.close();
    streamListeners = [];
}

export async function getAvailableLogs() {
    let response = await fetch(url(`/api/datalogs`, {}));
    return await response.json();
}
