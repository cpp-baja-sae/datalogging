#!/usr/bin/env node

const cors = require('cors');
const express = require('express');
const fs = require('fs');
const fsp = require('fs').promises;
const http = require('http');
const path = require('path');
const ws = require('ws');

const ipc = require('./ipc');

// Must not end with a slash.
const data_dir = '/root/datalogs';

function frame_length_from_format(format) {
    let total_size = 0;
    const format_sizes = {
        unorm16: 2,
        snorm16: 2,
        dummy8: 1,
        dummy64: 8
    };
    for (let item of format.layout) {
        total_size += format_sizes[item.type]
    }
    return total_size;
}

// Wrap everything in an anonymous async method so we can use await keyword.
(async () => {
    console.log('Creating server objects...');
    let app = express();
    let server = http.createServer(app);
    let ws_server = new ws.Server({ server });

    console.log('Connecting to Crunch...');
    let command_ipc = await ipc.connect_ipc();
    let ipc_stream = await ipc.connect_stream();
    const default_format = await command_ipc.send_command(ipc.COMMAND_GET_FORMAT, []);
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

    ipc_stream.on('data', (data) => {
        if (ws_server.clients.size === 0) {
            // Don't bother if no one's connected.
            // TODO: If everyone is disconnected, lower the sample rate?
            return;
        }

        ws_server.clients.forEach(client => {
            client.send(new Uint8Array(data));
        });
    });

    console.log('Configuring Express endpoints...');

    // This way we can use the React dev server while prototyping the UI.
    // We can also develop the client on a faster, more capable computer while
    // still being able to access data from the PI, because the react dev server
    // is slow af with that wimpy 1GHz processor.
    app.use(cors());
    app.use(express.json());

    app.get('/api/default_format', async (req, res) => {
        res.status(200).contentType('json').send(default_format);
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
            return;
        }

        let info = await fsp.readFile(folder + '/info.json');
        info = JSON.parse(info);
        let bytes_per_batch = info.num_adcs * info.num_channels * 2;
        let start = parseInt(req.query.start) * bytes_per_batch;
        let end = parseInt(req.query.end) * bytes_per_batch;
        let data_path = folder + '/' + req.query.lod + '.bin';
        let segment_stream = fs.createReadStream(data_path, {
            start: start,
            end: end,
        });

        res.status(200);
        // Arbitrary binary data.
        res.contentType('application/octet-stream');
        // Pipe in data read directly from the file.
        segment_stream.pipe(res);
        segment_stream.on('end', () => {
            res.end();
        });
    });

    // Serve user interface from /ui/*.
    app.use('/ui', express.static('../client/build/'));

    console.log('Initialization complete! Running server.');

    server.listen(80);

})();