import urllib from 'url';
import { ParsedUrlQueryInput } from 'querystring';
import { RawDataFrame, DataFormat } from '../data/types';

const PLACEHOLDER_DATA = false;

// Utilities

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

// Websocket stuff

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

// API Endpoints

export async function readDataSpan(date: number, start: number, end: number, lod: number) {
  let response = await fetch(url(`/api/datalogs/${date}/span`, {
    start: start,
    end: end,
    lod: lod,
  }));
  return await response.arrayBuffer();
}

export async function getAvailableLogs() {
  let response = await fetch(url(`/api/datalogs`, {}));
  return await response.json();
}

// Settings
class Setting<T> {
  key: string;
  value: T | null;
  initialPromise: Promise<T>;
  initialPromiseComplete: boolean;
  listeners: Array<(newValue: T) => void>;

  constructor(key: string) {
    this.key = key;
    this.value = null;
    this.initialPromise = this._get();
    this.initialPromiseComplete = false;
    this.listeners = [];
    this.initialPromise.then(value => {
      this.value = value;
      this.initialPromiseComplete = true;
    });
  }

  async _get(): Promise<T> {
    let response = await fetch(url('/api/settings/' + this.key, {}));
    return (await response.json())[this.key];
  }

  async _set(value: T): Promise<void> {
    let body: any = {};
    body[this.key] = value;
    await fetch(
      url('/api/settings/' + this.key, {}), {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(body),
      }
    );
  }

  async set(newValue: T): Promise<void> {
    if (!this.initialPromiseComplete) {
      await this.initialPromise;
    }
    await this._set(newValue);
    this.value = newValue;
    for (let listener of this.listeners) {
      listener(newValue);
    }
  }

  async getOnce(): Promise<T> {
    if (this.initialPromiseComplete) {
      return this.value as T;
    } else {
      return this.initialPromise;
    }
  }

  // This listener will be called whenever the value changes in the future.
  subscribe(listener: (newValue: T) => void) {
    this.listeners.push(listener);
  }

  unsubscribe(listener: (newValue: T) => void) {
    this.listeners = this.listeners.filter(element => element !== listener);
  }
}

export const settings = {
  default_format: new Setting<DataFormat>('default_format'),
  stream_lod: new Setting<number>('stream_lod'),
}
