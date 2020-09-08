import urllib from 'url';
import { ParsedUrlQueryInput } from 'querystring';
import { RawDataFrame } from '../data/types';

const PLACEHOLDER_DATA = false;

function url(endpoint: string, query?: ParsedUrlQueryInput) {
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

function wsUrl(endpoint: string) {
  if (process.env.NODE_ENV === 'development') {
    // If we are running the React dev server, then the API endpoints are 
    // technically hosted on another server.
    return `ws://raspberrypi.local${endpoint}`;
  } else {
    // Otherwise, it's fine to use the relative path.
    return `ws://${window.location.hostname}`;
  }
}

export async function readDataSpan(date: number, start: number, end: number, lod: number) {
  let response = await fetch(url(`/api/datalogs/${date}/span`, {
    start: start,
    end: end,
    lod: lod,
  }));
  return await response.arrayBuffer();
}

let streamConnection: WebSocket | null = null;
let streamListeners: Array<(frame: RawDataFrame) => void> = [];

// TODO: New format placeholder data.
if (PLACEHOLDER_DATA) {
  setInterval(() => {
    for (let listener of streamListeners) {
      // listener(dataFrame);
    }
  }, 100);
}

export async function addStreamListener(listener: (frame: RawDataFrame) => void) {
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
