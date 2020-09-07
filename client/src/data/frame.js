import { BUFFER_LENGTH } from '../util/constants.js';

// How many bytes each kind of item takes.
const itemTypeSizes = {
  unorm16: 2,
  snorm16: 2,
  dummy8: 2,
  dummy64: 2,
};

const itemParseFns = {
  unorm16: (dataBuffer, itemStartIndex) => {
    let intVal = (dataBuffer[itemStartIndex] << 8) + dataBuffer[itemStartIndex + 1];
    return intVal / 0xFFFF;
  },
  snorm16: (dataBuffer, itemStartIndex) => {
    let intVal = (dataBuffer[itemStartIndex] << 8) + dataBuffer[itemStartIndex + 1];
    if (intVal >= 0x8000) {
      intVal -= 0x10000;
    }
    return (intVal / 0x7FFF);
  },
  dummy8: (_dataBuffer, _itemStartIndex) => 0,
  dummy64: (_dataBuffer, _itemStartIndex) => 0,
};

// Returns a function which accepts a data bufffer (Uint8Array) as its first
// argument and the position where the frame starts in that buffer as its
// second argument. Given the data format provided, it will return a list of
// parsed elements from that frame. Also returns the length of a data frame in
// bytes.
function makeFrameParser(dataLayout) {
  let parseFunctions = [];
  let itemSizes = [];
  for (let item of dataLayout) {
    if (itemParseFns[item.type] === undefined) {
      throw new Error(`There is no item type named "${item.type}".`);
    }
    parseFunctions.push(itemParseFns[item.type]);
    itemSizes.push(itemTypeSizes[item.type]);
  }
  let parser = (dataBuffer, frameStartIndex) => {
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
function makeLowResFrameParser(dataLayout) {
  let { parser, frameSize } = makeFrameParser(dataLayout);
  return {
    parser: (dataBuffer, frameStartIndex) => [
      parser(dataBuffer, frameStartIndex),
      parser(dataBuffer, frameStartIndex + frameSize),
      parser(dataBuffer, frameStartIndex + 2 * frameSize)
    ],
    frameSize: frameSize * 3,
  };
}

export class FrameBuffer {
  constructor(dataFormat) {
    this.storage = new Array(BUFFER_LENGTH);
    this.format = dataFormat;
    this.parser = makeFrameParser(dataFormat.layout).parser;
  }

  storeRawFrame(index, rawFrameData) {
    let dataBuffer = new Uint8Array(rawFrameData);
    this.storage[index] = this.parser(dataBuffer, 0);
  }

  // Since this buffer stores max-res frames, the "minimum" and "maximum"
  // values at any point are just the plain value at that point.
  getMin(frameIndex, channelIndex) {
    return this.storage[frameIndex][channelIndex];
  }

  getMax(frameIndex, channelIndex) {
    return this.storage[frameIndex][channelIndex];
  }

  getValue(frameIndex, channelIndex) {
    return this.storage[frameIndex][channelIndex];
  }
}

export class LowResFrameBuffer {
  constructor(dataFormat) {
    this.storage = new Array(BUFFER_LENGTH);
    this.format = dataFormat;
    this.parser = makeLowResFrameParser(dataFormat.layout).parser;
  }

  storeRawFrame(index, rawFrameData) {
    let dataBuffer = new Uint8Array(rawFrameData);
    this.storage[index] = this.parser(dataBuffer, 0);
  }

  getMin(frameIndex, channelIndex) {
    return this.storage[frameIndex][0][channelIndex];
  }

  getMax(frameIndex, channelIndex) {
    return this.storage[frameIndex][1][channelIndex];
  }

  getValue(frameIndex, channelIndex) {
    return this.storage[frameIndex][2][channelIndex];
  }
}
