const { exec } = require('child_process');
const fs = require('fs');
const fsp = require('fs').promises;

const USB_PORT_PATH = '/dev/ttyACM0';
const METADATA_INDEX = 15;
const DOWNLOAD_STORAGE = '/tmp/datalogging_downloads/';

function configureUsbPort() {
    const command = 'stty '
        + '-F ' + USB_PORT_PATH + ' '
        + 'cs8 9600 '
        + 'ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten '
        + '-echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts ';
    exec(command, (error, _stdout, stderr) => {
        if (error) {
            console.error('Failed to set up USB connection: ' + error);
            throw new Error('Failed to set up USB connection.');
        } else if (stderr) {
            console.error('Failed to set up USB connection: ' + stderr);
            throw new Error('Failed to set up USB connection.');
        }
    });
}

// Downloads a file from the datalogger to a temporary location, returning the 
// path it was downloaded to when complete.
async function downloadFile(slotIndex, fileIndex, sizeCallback) {
    configureUsbPort();
    const writeStream = fs.createWriteStream(USB_PORT_PATH);
    await new Promise(res => {
        writeStream.on("ready", res);
    });
    writeStream.write(new Uint8Array([fileIndex & 0x0F | 0x00, slotIndex & 0xFF]));
    writeStream.removeAllListeners();
    writeStream.close();

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

    const stream = fs.createReadStream(USB_PORT_PATH);
    // The size of the file should be transmitted in a single packet.
    const size = await new Promise((res, rej) => {
        stream.on("data", data => {
            stream.removeAllListeners();
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
            stream.on("data", data => {
                downloadTarget.write(data);
                remaining -= data.length;
                if (remaining === 0) res();
                if (remaining < 0) {
                    throw new Error('Received more data than expected!');
                }
            });
        });
        stream.removeAllListeners();
    }
    stream.close();
    downloadTarget.close();
    console.log('Download complete!');
    return filePath;
}

module.exports = {
    downloadFile,
    METADATA_INDEX,
};
