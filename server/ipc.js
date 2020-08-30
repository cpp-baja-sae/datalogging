const net = require('net');

// The name of the socket to connect to to be able to control Crunch.
const IPC_ID = '/tmp/.crunch_ipc';
// The name of the socket where we can get realtime data.
const IPC_STREAM_ID = '/tmp/.crunch_stream';
const IPC_COMMAND_STOP = 'x'.charCodeAt(0);
const IPC_COMMAND_BEGIN_FILE = 'b'.charCodeAt(0);
const IPC_COMMAND_END_FILE = 'e'.charCodeAt(0);

async function delay(milliseconds) {
    return new Promise((resolve, _) => {
        setTimeout(resolve, milliseconds);
    });
}

async function connect_ipc() {
    let crunch_ipc = net.createConnection(IPC_ID);
    let response_listeners = [];

    // Command should be an int, payload should be an array-like object.
    crunch_ipc.send_command = (command, payload) => {
        let response_listener = {
            command: command,
            resolve: (_data) => console.error('Resolve command not set.'),
            reject: () => console.error('Reject command not set.'),
        };
        response_listeners.push(response_listener);
        let response_promise = new Promise((resolve, reject) => {
            response_listener.resolve = resolve;
            response_listener.reject = reject;
        });

        let length = 1 + payload.length;
        if (length > 0xFF) {
            response_listener.reject();
            throw Error(`Message has ${length} bytes, must be less than 256.`);
        }
        let message = [length, command].concat(payload);
        crunch_ipc.write(new Uint8Array(message));

        return response_promise;
    };

    crunch_ipc.on('data', (data) => {
        let for_command = data[0];
        let next_listener = response_listeners.splice(0, 1)[0];
        if (next_listener.command === for_command) {
            next_listener.resolve(data);
        } else {
            console.error('Communication error!');
            next_listener.reject();
        }
    });

    return new Promise((resolve, _) => {
        crunch_ipc.on('connect', () => resolve(crunch_ipc));
    });
}

async function connect_stream() {
    let crunch_stream = net.createConnection(IPC_STREAM_ID);

    return new Promise((resolve, _) => {
        crunch_stream.on('connect', () => resolve(crunch_stream));
    });
}

module.exports = {
    connect_ipc: connect_ipc,
    connect_stream: connect_stream,
};