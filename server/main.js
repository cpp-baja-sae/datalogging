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

// Wrap everything in an anonymous async method so we can use await keyword.
(async () => {
    console.log('Creating server objects...');
    let app = express();
    let server = http.createServer(app);
    let ws_server = new ws.Server({ server });

    console.log('Connecting to Crunch...');
    let crunch_ipc = await ipc.connect_ipc();
    let crunch_stream = await ipc.connect_stream();

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

    crunch_stream.on('data', (data) => {
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
    app.use(cors());

    app.get('/api/datalogs', async (req, res) => {
        let datalog_folders = await fsp.readdir(data_dir);
        datalog_folders = datalog_folders.filter(item => item.indexOf('datalog_') === 0);
        const results = [];
        for (const folder of datalog_folders) {
            let filePath = path.join(data_dir, folder, 'info.json');
            try {
                let fileContents = await fsp.readFile(filePath);
                const info = JSON.parse(fileContents);
                const batches_per_second = (1000 * 1000) / info.cycle_time_us;
                // 2 bytes per sample.
                const bytes_per_second = batches_per_second * info.num_adcs * info.num_channels * 2;
                const lod0_stat = await fsp.stat(path.join(data_dir, folder, '0.bin'));
                const duration = Math.floor(lod0_stat.size / bytes_per_second);
                results.push({
                    date: folder.substr(8), // Skip 'datalog_'
                    duration,
                    ...info
                });
            } catch (e) {
                console.warn("WARNING: Data log may be corrupt at " + filePath);
            }
        }
        res.status(200).send({ list: results });
    })

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
    app.use('/ui', express.static('../frontend/build/'));

    console.log('Initialization complete! Running server.');

    server.listen(80);

})();