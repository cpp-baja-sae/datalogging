const { exec } = require('child_process');
const fs = require('fs');
const fsp = require('fs').promises;
const SerialPort = require('serialport');

const USB_PORT_PATH = '/dev/ttyACM0';
const METADATA_INDEX = 15;
const DOWNLOAD_STORAGE = '/tmp/datalogging_downloads/';

function openUsbPort() {
    const usb = new SerialPort(USB_PORT_PATH, {
        autoOpen: true,
        baudRate: 9600,
        dataBits: 8,
        stopBits: 1,
        parity: 'none',
        lock: false,
    });
    usb.on('error', console.error);
    usb.awaitEvent = async (eventName) => {
        return new Promise(res => {
            usb.once(eventName, res);
        });
    };
    return usb;
}

async function sendCommand(command, arg1, arg2) {
    const usb = openUsbPort();
    usb.write(new Uint8Array([command << 4 | arg1 & 0xF, arg2 & 0xFF]));
    usb.end();
    await usb.awaitEvent('finish');
    return usb;
}

// Downloads a file from the datalogger to a temporary location, returning the 
// path it was downloaded to when complete.
async function downloadFile(slotIndex, fileIndex, sizeCallback) {
    const usb = await sendCommand(0x0, fileIndex, slotIndex);

    try {
        await fsp.mkdir(DOWNLOAD_STORAGE);
    } catch {
        // If it already exists we don't need to do anything.
    }
    const filePath = DOWNLOAD_STORAGE + slotIndex + '-' + fileIndex;
    try {
        await fsp.unlink(filePath);
    } catch {
        // If it's nonexistant then we don't need to do anything.
    }
    const downloadTarget = fs.createWriteStream(filePath);

    // The size of the file should be transmitted in a single packet.
    const size = await new Promise((res, rej) => {
        usb.on("data", data => {
            usb.removeAllListeners();
            if (data.length >= 8) {
                // My version of NodeJS doesn't have readBigUInt64LE.
                // This comes with the problem that numbers over 2^53-1 won't
                // be accurately represented but as this would only be encountered
                // with an 8,192TB file I don't think it's a problem.
                // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/BigInt
                let value = data.readUInt32LE() + (1 << 32) * data.readUInt32LE(4);
                if (data.length > 8) {
                    downloadTarget.write(data.subarray(8));
                    value -= data.length - 8;
                }
                res(value);
            } else {
                rej(new Error('Expected an 8-byte value, got ' + data));
            }
        });
    });
    console.log('Downloading ' + size + 'B of data.');
    if (sizeCallback) {
        sizeCallback(size);
    }
    // await new Promise(res => downloadTarget.on('ready', res));
    if (size > 0) {
        await new Promise((res, rej) => {
            let remaining = size;
            usb.on('data', data => {
                downloadTarget.write(data);
                remaining -= data.length;
                if (remaining === 0) {
                    usb.close();
                    res();
                }
                if (remaining < 0) {
                    throw new Error('Received more data than expected!');
                }
            });
        });
    }
    downloadTarget.close();
    console.log('Download complete!');
    return filePath;
}

// Gets the JSON object describing the current format that the datalogger is
// recording in.
async function getDataFormat() {
    const usb = await sendCommand(1, 0, 0);

    let buffer = Buffer.alloc(0);
    let expectedSize = 0;
    usb.on('error', console.error);
    await new Promise((res, rej) => {
        usb.on('data', data => {
            if (expectedSize === 0) {
                // We are waiting to see how many bytes we need to read.
                expectedSize = data.readUInt32LE();
                data = data.subarray(4);
            }
            buffer = Buffer.concat([buffer, data]);
            if (buffer.length > expectedSize) {
                rej(new Error('Received more data than expected!'));
            } else if (buffer.length === expectedSize) {
                // For some reason this has to be *inside* the event handler or
                // the server will hang when trying to exit.
                usb.close();
                res();
            }
        });
    });
    return JSON.parse(buffer.toString('utf-8'));
}

module.exports = {
    downloadFile,
    getDataFormat,
    METADATA_INDEX,
};
