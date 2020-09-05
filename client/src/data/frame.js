
// How many bytes each kind of item takes.
const itemTypeSizes = {
    unorm16: 2
};

const itemParseFns = {
    unorm16: (dataBuffer, itemStartIndex) => {
        let intVal = (dataBuffer[itemStartIndex] << 8) + dataBuffer[itemStartIndex + 1];
        return intVal / 0xFFFF;
    }
};

// Returns a function which accepts a data bufffer (Uint8Array) as its first
// argument and the position where the frame starts in that buffer as its
// second argument. Given the data format provided, it will return a list of
// parsed elements from that frame. Also returns the length of a data frame in
// bytes.
export function makeFrameParser(dataFormat) {
    let parseFunctions = [];
    let itemSizes = [];
    for (let item of dataFormat) {
        if (itemParseFns[item.type] == undefined) {
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
// The returned value is an array in the form [averages, minimums, maximums].
export function makeLowResFrameParser(dataFormat) {
    let subFrameParser = makeFrameParser(dataFormat);
}
