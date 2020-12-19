#!/usr/bin/env node

const cors = require('cors');
const express = require('express');
const fs = require('fs');
const fsp = require('fs').promises;
const http = require('http');
const path = require('path');
const ws = require('ws');

const collectorComms = require('./collectorComms');

// Must not end with a slash.
const dataDir = '/root/datalogs';

const FORMAT_SIZES = {
    unorm16: 2,
    snorm16: 2,
    uint8: 1,
    error_code: 1,
    dummy8: 1,
    dummy64: 8
};

// The maximum characters it takes to represent each data type in an exported CSV file.
const FORMAT_CSV_SIZES = {
    unorm16: 7,
    snorm16: 8,
    uint8: 3,
    error_code: 3,
    dummy8: 1,
    dummy64: 1
};

// Represent the value as text going into a CSV file.
const FORMAT_PARSERS = {
    unorm16: (buffer, offset) => (buffer.readUInt16LE(offset) / 0xFFFF).toFixed(5),
    snorm16: (buffer, offset) => (buffer.readInt16LE(offset) / 0x7FFF).toFixed(5),
    uint8: (buffer, offset) => buffer.readUInt8(offset).toFixed(0),
    error_code: (buffer, offset) => buffer.readUInt8(offset).toFixed(0),
    dummy8: (_buffer, _offset) => '0',
    dummy64: (_buffer, _offset) => '0',
};

function frameLengthFromFormat(format) {
    let totalSize = 0;
    for (let item of format.layout) {
        totalSize += FORMAT_SIZES[item.type]
    }
    return totalSize;
}

// Wrap everything in an anonymous async method so we can use await keyword.
(async () => {
    console.log('Creating server objects...');
    let app = express();
    let server = http.createServer(app);
    let wsServer = new ws.Server({ server });

    const defaultFormat = await collectorComms.getDataFormat();
    const frameSize = frameLengthFromFormat(defaultFormat);

    console.log('Configuring web socket server...');
    wsServer.on('connection', (connection) => {
        connection.alive = true;
        connection.on('pong', () => connection.alive = true);
    });

    // Check every 10 seconds to make sure clients are still connected.
    setInterval(() => {
        wsServer.clients.forEach(client => {
            if (!client.alive) {
                client.terminate();
                return;
            }
            client.alive = false;
            client.ping();
        });
    }, 10000);

    // ipcStream.on('data', (data) => {
    //     if (wsServer.clients.size === 0) {
    //         // Don't bother if no one's connected.
    //         // TODO: If everyone is disconnected, lower the sample rate?
    //         return;
    //     }

    //     wsServer.clients.forEach(client => {
    //         client.send(new Uint8Array(data));
    //     });
    // });

    console.log('Configuring Express endpoints...');

    // This way we can use the React dev server while prototyping the UI.
    app.use(cors());
    app.use(express.json());

    // Only a get for this one because it's set in stone.
    app.get('/api/settings/defaultFormat', async (req, res) => {
        res.status(200).contentType('json').send({ defaultFormat: defaultFormat });
    });

    // The LOD that is being streamed to the client.
    app.get('/api/settings/streamLod', async (req, res) => {
        let value = await commandIpc.sendCommand(ipc.COMMAND_GET_STREAM_LOD, []);
        res.status(200).contentType('json').send({
            streamLod: value[0]
        });
    });

    app.put('/api/settings/streamLod', async (req, res) => {
        if (!req.body.streamLod) {
            res.status(400).contentType('json').send({error: 'Missing required parameter "streamLod" in body.'});
            return;
        }
        await commandIpc.sendCommand(ipc.COMMANDSETSTREAMLOD, [req.body.streamLod]);
        // realtimeStreamUsesLowResFrames = req.body.streamLod > 0;
        res.sendStatus(201);
    });

    app.get('/api/datalogs', async (req, res) => {
        let datalogFolders = await fsp.readdir(dataDir);
        datalogFolders = datalogFolders.filter(item => item.indexOf('datalog') === 0);
        const results = [];
        for (const folder of datalogFolders) {
            let filePath = path.join(dataDir, folder, 'format.json');
            try {
                let fileContents = await fsp.readFile(filePath);
                const format = JSON.parse(fileContents);
                const framesPerSecond = (1000 * 1000) / format.frameTimeUs;
                const bytesPerSecond = frameLengthFromFormat(format) * framesPerSecond;
                const lod0_stat = await fsp.stat(path.join(dataDir, folder, '0.bin'));
                const duration = Math.floor(lod0_stat.size / bytesPerSecond);
                results.push({
                    date: folder.substr(8), // Skip 'datalog'
                    duration,
                    ...format
                });
            } catch (e) {
                console.warn("WARNING: Data log may be corrupt at " + filePath);
            }
        }
        res.status(200).send({ list: results });
    });

    async function openSegmentStream(req, res) {
        let folder = 'datalog' + ('' + req.params.date).padStart(20, '0');
        folder = dataDir + '/' + folder;
        try {
            await fsp.stat(folder);
        } catch {
            res.status(404).send({
                status: 'error',
                error: 'fileNot_found',
                description: 'Could not find a datalog file with the date '
                    + req.params.date
            });
            return [null, null];
        }

        let format = await fsp.readFile(folder + '/format.json');
        format = JSON.parse(format);
        let bytesPerFrame = frameLengthFromFormat(format);
        if (req.query.lod > 0) bytesPerFrame *= 3;
        let start = parseInt(req.query.start) * bytesPerFrame;
        let end = parseInt(req.query.end) * bytesPerFrame;
        let dataPath = folder + '/' + req.query.lod + '.bin';
        let stream = fs.createReadStream(dataPath, {
            start: start,
            end: end,
        });
        return [format, stream];
    }

    app.get('/api/datalogs/:date/span', async (req, res) => {
        if (
            !req.query.start
            || !req.query.end
            || !req.query.lod
        ) {
            res.status(400).send({
                status: 'error',
                error: 'query',
                description: 'Request must contain query paramters start, end, '
                    + 'and lod.'
            });
            return;
        }

        let [_format, segmentStream] = await openSegmentStream(req, res);
        if (!segmentStream) return;

        res.status(200);
        // Arbitrary binary data.
        res.contentType('application/octet-stream');
        // Pipe in data read directly from the file.
        segmentStream.pipe(res);
        segmentStream.on('end', () => {
            res.end();
        });
    });

    app.get('/api/datalogs/:date/csv', async (req, res) => {
        if (
            !req.query.start
            || !req.query.end
            || !req.query.lod
            || !req.query.channels
        ) {
            res.status(400).send({
                status: 'error',
                error: 'query',
                description: 'Request must contain query parameters start, '
                    + 'end, lod, and channels.'
            });
            return;
        }
        let channels = req.query.channels;
        if (typeof channels !== typeof []) {
            channels = [channels];
        }
        channels = channels.map(x => parseInt(x));

        let [format, segmentStream] = await openSegmentStream(req, res);
        if (!segmentStream) return;

        res.status(200).contentType('text/csv');

        let header = 'time [ms],';
        if (req.query.lod === '0') {
            for (let channel of channels) {
                header += format.layout[channel].group + '/' + format.layout[channel].name + ',';
            }
        } else {
            for (let type of [' [min]', ' [max]', ' [avg]']) {
                for (let channel of channels) {
                    header += format.layout[channel].group + '/' + format.layout[channel].name + type + ',';
                }
            }
        }
        res.write(header + '\n');

        let currentChannelIndex = 0;
        let currentSubframe = 0;
        let totalSubframes = req.query.lod == 0 ? 1 : 3;
        let timePerFrame = format.frameTimeUs / (1000 * 1000);
        let time = req.query.start * timePerFrame;
        let line = '' + (time * 1000).toFixed(1) + ',';
        let leftoverBytes = null;
        segmentStream.on('data', (chunk) => {
            if (leftoverBytes !== null) {
                chunk = Buffer.concat([leftoverBytes, chunk]);
            }
            let readPointer = 0;
            let type = format.layout[currentChannelIndex].type;
            let size = FORMAT_SIZES[type];
            while (readPointer + size <= chunk.length) {
                if (channels.includes(currentChannelIndex)) {
                    line += FORMAT_PARSERS[type](chunk, readPointer) + ',';
                }
                readPointer += size;
                currentChannelIndex += 1;
                if (currentChannelIndex === format.layout.length) {
                    currentChannelIndex = 0;
                    currentSubframe += 1;
                    if (currentSubframe === totalSubframes) {
                        currentSubframe = 0;
                        res.write(line + '\n');
                        time += timePerFrame;
                        line = '' + (time * 1000).toFixed(1) + ',';
                    }
                }
                type = format.layout[currentChannelIndex].type;
                size = FORMAT_SIZES[type];
            }
            if (readPointer !== chunk.length) {
                leftoverBytes = chunk.slice(readPointer);
            } else {
                leftoverBytes = null;
            }
        });
        segmentStream.on('end', () => {
            res.end();
        });
    });

    async function estimateCsvSize(req, res) {
        if (
            !req.query.start
            || !req.query.end
            || !req.query.lod
        ) {
            res.status(400).send({
                status: 'error',
                error: 'query',
                description: 'Request must contain query parameters start, '
                    + 'end, lod, and channels.'
            });
            return;
        }

        if (req.query.end < req.query.start) {
            return 0;
        }

        let channels = req.query.channels;
        if (channels === undefined) {
            channels = [];
        } else if (typeof channels !== typeof []) {
            channels = [channels];
        }
        channels = channels.map(x => parseInt(x));

        let [format, segmentStream] = await openSegmentStream(req, res);
        if (!format) return;
        // Close the file since we don't need it.
        segmentStream.destroy();
        let lineLength = channels.length + 1 + 10; // Commas and newline and timestamp.
        for (let channel of channels) {
            linelength += FORMAT_CSV_SIZES[format.layout[channel].type];
        }
        if (req.query.lod > 0) lineLength *= 3;
        return lineLength * (req.query.end - req.query.start);
    }

    app.get('/api/datalogs/:date/csvEstimate', async (req, res) => {
        res.status(200).send({ estimate: await estimateCsvSize(req, res) });
    });

    // Serve user interface from /ui/*.
    app.use('/ui', express.static('../client/build/'));

    console.log('Initialization complete! Running server.');

    server.listen(8080);

});//();

(async () => {
    // console.log(await collectorComms.downloadFile(4, 15));
    console.log((await collectorComms.getSlotStatuses()).join(' '));
    return;
    for (let i = 0; i < 8; i++) {
        console.log(await collectorComms.startNewRecording());
        console.log('\n');
        console.log((await collectorComms.getSlotStatuses()).join(' '));
        await new Promise(res => setTimeout(res, 5000));
    }
})();