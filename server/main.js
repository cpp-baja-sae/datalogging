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
const data_dir = '/root/datalogs';

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

function frame_length_from_format(format) {
    let total_size = 0;
    for (let item of format.layout) {
        total_size += FORMAT_SIZES[item.type]
    }
    return total_size;
}

// Wrap everything in an anonymous async method so we can use await keyword.
(async () => {
    console.log('Creating server objects...');
    let app = express();
    let server = http.createServer(app);
    let ws_server = new ws.Server({ server });

    // const default_format 
    //     = JSON.parse((await command_ipc.send_command(ipc.COMMAND_GET_FORMAT, [])).toString('utf-8'));
    // const frame_size = frame_length_from_format(default_format);

    console.log('Configuring web socket server...');
    ws_server.on('connection', (connection) => {
        connection.alive = true;
        connection.on('pong', () => connection.alive = true);
    });

    // Check every 10 seconds to make sure clients are still connected.
    setInterval(() => {
        ws_server.clients.forEach(client => {
            if (!client.alive) {
                client.terminate();
                return;
            }
            client.alive = false;
            client.ping();
        });
    }, 10000);

    // ipc_stream.on('data', (data) => {
    //     if (ws_server.clients.size === 0) {
    //         // Don't bother if no one's connected.
    //         // TODO: If everyone is disconnected, lower the sample rate?
    //         return;
    //     }

    //     ws_server.clients.forEach(client => {
    //         client.send(new Uint8Array(data));
    //     });
    // });

    console.log('Configuring Express endpoints...');

    // This way we can use the React dev server while prototyping the UI.
    // We can also develop the client on a faster, more capable computer while
    // still being able to access data from the PI, because the react dev server
    // is slow af with that wimpy 1GHz processor.
    app.use(cors());
    app.use(express.json());

    // Only a get for this one because it's set in stone.
    app.get('/api/settings/default_format', async (req, res) => {
        res.status(200).contentType('json').send({ default_format: default_format });
    });

    // The LOD that is being streamed to the client.
    app.get('/api/settings/stream_lod', async (req, res) => {
        let value = await command_ipc.send_command(ipc.COMMAND_GET_STREAM_LOD, []);
        res.status(200).contentType('json').send({
            stream_lod: value[0]
        });
    });

    app.put('/api/settings/stream_lod', async (req, res) => {
        if (!req.body.stream_lod) {
            res.status(400).contentType('json').send({error: 'Missing required parameter "stream_lod" in body.'});
            return;
        }
        await command_ipc.send_command(ipc.COMMAND_SET_STREAM_LOD, [req.body.stream_lod]);
        // realtime_stream_uses_low_res_frames = req.body.stream_lod > 0;
        res.sendStatus(201);
    });

    app.get('/api/datalogs', async (req, res) => {
        let datalog_folders = await fsp.readdir(data_dir);
        datalog_folders = datalog_folders.filter(item => item.indexOf('datalog_') === 0);
        const results = [];
        for (const folder of datalog_folders) {
            let filePath = path.join(data_dir, folder, 'format.json');
            try {
                let fileContents = await fsp.readFile(filePath);
                const format = JSON.parse(fileContents);
                const frames_per_second = (1000 * 1000) / format.frame_time_us;
                const bytes_per_second = frame_length_from_format(format) * frames_per_second;
                const lod0_stat = await fsp.stat(path.join(data_dir, folder, '0.bin'));
                const duration = Math.floor(lod0_stat.size / bytes_per_second);
                results.push({
                    date: folder.substr(8), // Skip 'datalog_'
                    duration,
                    ...format
                });
            } catch (e) {
                console.warn("WARNING: Data log may be corrupt at " + filePath);
            }
        }
        res.status(200).send({ list: results });
    });

    async function open_segment_stream(req, res) {
        let folder = 'datalog_' + ('' + req.params.date).padStart(20, '0');
        folder = data_dir + '/' + folder;
        try {
            await fsp.stat(folder);
        } catch {
            res.status(404).send({
                status: 'error',
                error: 'file_not_found',
                description: 'Could not find a datalog file with the date '
                    + req.params.date
            });
            return [null, null];
        }

        let format = await fsp.readFile(folder + '/format.json');
        format = JSON.parse(format);
        let bytes_per_frame = frame_length_from_format(format);
        if (req.query.lod > 0) bytes_per_frame *= 3;
        let start = parseInt(req.query.start) * bytes_per_frame;
        let end = parseInt(req.query.end) * bytes_per_frame;
        let data_path = folder + '/' + req.query.lod + '.bin';
        let stream = fs.createReadStream(data_path, {
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

        let [_format, segment_stream] = await open_segment_stream(req, res);
        if (!segment_stream) return;

        res.status(200);
        // Arbitrary binary data.
        res.contentType('application/octet-stream');
        // Pipe in data read directly from the file.
        segment_stream.pipe(res);
        segment_stream.on('end', () => {
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

        let [format, segment_stream] = await open_segment_stream(req, res);
        if (!segment_stream) return;

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
        let timePerFrame = format.frame_time_us / (1000 * 1000);
        let time = req.query.start * timePerFrame;
        let line = '' + (time * 1000).toFixed(1) + ',';
        let leftover_bytes = null;
        segment_stream.on('data', (chunk) => {
            if (leftover_bytes !== null) {
                chunk = Buffer.concat([leftover_bytes, chunk]);
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
                leftover_bytes = chunk.slice(readPointer);
            } else {
                leftover_bytes = null;
            }
        });
        segment_stream.on('end', () => {
            res.end();
        });
    });

    async function estimate_csv_size(req, res) {
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

        let [format, segment_stream] = await open_segment_stream(req, res);
        if (!format) return;
        // Close the file since we don't need it.
        segment_stream.destroy();
        let line_length = channels.length + 1 + 10; // Commas and newline and timestamp.
        for (let channel of channels) {
            line_length += FORMAT_CSV_SIZES[format.layout[channel].type];
        }
        if (req.query.lod > 0) line_length *= 3;
        return line_length * (req.query.end - req.query.start);
    }

    app.get('/api/datalogs/:date/csv_estimate', async (req, res) => {
        res.status(200).send({ estimate: await estimate_csv_size(req, res) });
    });

    // Serve user interface from /ui/*.
    app.use('/ui', express.static('../client/build/'));

    console.log('Initialization complete! Running server.');

    server.listen(8080);

});//();

(async () => {
    collectorComms.downloadFile(23, 5);
})();