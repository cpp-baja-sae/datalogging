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

export async function readDataSpan(date, start, end) {
  let response = await fetch(url(`/api/datalogs/${date}/span`, {
    start: start,
    end: end,
    lod: 0,
  }));
  return await response.arrayBuffer();
}

let streamConnection = null;
let streamListeners = [];

// TODO: New format placeholder data.
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
    let data = await event.data.arrayBuffer();
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

export async function getDefaultFormat() {
  let response = await fetch(url(`/api/default_format`, {}));
  return await response.json();
}
