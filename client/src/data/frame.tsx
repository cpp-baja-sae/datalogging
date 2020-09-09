import { BUFFER_LENGTH } from '../util/constants';
import { DataLayout, DataFormat, ParsedDataFrame, RawDataFrame, ParsedLowResDataFrame } from './types';

// How many bytes each kind of item takes.
const itemTypeSizes: any = {
  unorm16: 2,
  snorm16: 2,
  dummy8: 1,
  dummy64: 8,
};

type ItemParseFn = (dataBuffer: Uint8Array, itemStartIndex: number) => any;
const itemParseFns: any = {
  unorm16: (dataBuffer: Uint8Array, itemStartIndex: number) => {
    let intVal = (dataBuffer[itemStartIndex + 1] << 8) + dataBuffer[itemStartIndex];
    return intVal / 0xFFFF;
  },
  snorm16: (dataBuffer: Uint8Array, itemStartIndex: number) => {
    let intVal = (dataBuffer[itemStartIndex + 1] << 8) + dataBuffer[itemStartIndex];
    if (intVal >= 0x8000) {
      intVal -= 0x10000;
    }
    return (intVal / 0x7FFF);
  },
  dummy8: (_dataBuffer: Uint8Array, _itemStartIndex: number) => 0,
  dummy64: (_dataBuffer: Uint8Array, _itemStartIndex: number) => 0,
};

// Returns a function which accepts a data bufffer (Uint8Array) as its first
// argument and the position where the frame starts in that buffer as its
// second argument. Given the data format provided, it will return a list of
// parsed elements from that frame. Also returns the length of a data frame in
// bytes.
function makeFrameParser(dataLayout: DataLayout) {
  let parseFunctions: Array<ItemParseFn> = [];
  let itemSizes: Array<number> = [];
  for (let item of dataLayout) {
    if (itemParseFns[item.type] === undefined) {
      throw new Error(`There is no item type named "${item.type}".`);
    }
    parseFunctions.push(itemParseFns[item.type]);
    itemSizes.push(itemTypeSizes[item.type]);
  }
  let parser = (dataBuffer: Uint8Array, frameStartIndex: number): ParsedDataFrame => {
    let currentItemIndex = frameStartIndex;
    let parsedData = [];
    for (let index = 0; index < parseFunctions.length; index++) {
      parsedData.push(parseFunctions[index](dataBuffer, currentItemIndex));
      currentItemIndex += itemSizes[index];
    }
    return parsedData;
  };
  let frameSize = itemSizes.reduce((sum, element) => sum + element, 0);
  return { parser, frameSize };
}

// Similar to makeFrameParser(), but designed to work on low res frames which 
// include information about the minimum and maximum values during the frame.
// The returned value is an array in the form [minimums, maximums, averages].
function makeLowResFrameParser(dataLayout: DataLayout) {
  let { parser, frameSize } = makeFrameParser(dataLayout);
  return {
    parser: (dataBuffer: Uint8Array, frameStartIndex: number): ParsedLowResDataFrame => [
      parser(dataBuffer, frameStartIndex),
      parser(dataBuffer, frameStartIndex + frameSize),
      parser(dataBuffer, frameStartIndex + 2 * frameSize)
    ],
    frameSize: frameSize * 3,
  };
}

export function frameSizeFromFormat(format: DataFormat): number {
  let size = 0;
  for (let item of format.layout) {
    if (itemParseFns[item.type] === undefined) {
      throw new Error(`There is no item type named "${item.type}".`);
    }
    size += itemTypeSizes[item.type];
  }
  return size;
}

export interface GenericFrameBuffer {
  storeRawFrame: (index: number, rawFrameData: RawDataFrame) => void;
  getMin: (frameIndex: number, channelIndex: number) => any;
  getMax: (frameIndex: number, channelIndex: number) => any;
  getValue: (frameIndex: number, channelIndex: number) => any;
}

export class FrameBuffer implements GenericFrameBuffer {
  storage: Array<ParsedDataFrame>;
  format: DataFormat;
  parser: (dataBuffer: Uint8Array, frameStartIndex: number) => ParsedDataFrame;

  constructor(dataFormat: DataFormat) {
    this.storage = new Array(BUFFER_LENGTH);
    this.format = dataFormat;
    this.parser = makeFrameParser(dataFormat.layout).parser;
  }

  storeRawFrame(index: number, rawFrameData: RawDataFrame) {
    let dataBuffer = new Uint8Array(rawFrameData);
    this.storage[index] = this.parser(dataBuffer, 0);
  }

  // Since this buffer stores max-res frames, the "minimum" and "maximum"
  // values at any point are just the plain value at that point.
  getMin(frameIndex: number, channelIndex: number) {
    return this.storage[frameIndex][channelIndex];
  }

  getMax(frameIndex: number, channelIndex: number) {
    return this.storage[frameIndex][channelIndex];
  }

  getValue(frameIndex: number, channelIndex: number) {
    return this.storage[frameIndex][channelIndex];
  }
}

export class LowResFrameBuffer implements GenericFrameBuffer {
  storage: Array<ParsedLowResDataFrame>;
  format: DataFormat;
  parser: (dataBuffer: Uint8Array, frameStartIndex: number) => ParsedLowResDataFrame;

  constructor(dataFormat: DataFormat) {
    this.storage = new Array(BUFFER_LENGTH);
    this.format = dataFormat;
    this.parser = makeLowResFrameParser(dataFormat.layout).parser;
  }

  storeRawFrame(index: number, rawFrameData: RawDataFrame) {
    let dataBuffer = new Uint8Array(rawFrameData);
    this.storage[index] = this.parser(dataBuffer, 0);
  }

  getMin(frameIndex: number, channelIndex: number) {
    return this.storage[frameIndex][0][channelIndex];
  }

  getMax(frameIndex: number, channelIndex: number) {
    return this.storage[frameIndex][1][channelIndex];
  }

  getValue(frameIndex: number, channelIndex: number) {
    return this.storage[frameIndex][2][channelIndex];
  }
}
