const net = require('net');

// The name of the socket to connect to to be able to control Crunch.
const IPC_ID = '/tmp/.crunch_ipc';
// The name of the socket where we can get realtime data.
const IPC_STREAM_ID = '/tmp/.crunch_stream';

async function delay(milliseconds) {
    return new Promise((resolve, _) => {
        setTimeout(resolve, milliseconds);
    });
}

async function connect_ipc() {
    let crunch_ipc = net.createConnection(IPC_ID);
    let response_listeners = [];
    let current_listener = null;

    // Command should be an int, payload should be an array-like object.
    crunch_ipc.send_command = (command, payload) => {
        let response_listener = {
            command: command,
            data_size: -1,
            current_data: [],
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
        let current_byte = 0;
        while (current_byte < data.length) {
            if (current_listener == null) {
                current_listener = response_listeners.splice(0, 1)[0];
                current_listener.data_size = data[current_byte] << 8 | data[current_byte + 1];
                current_byte += 2;
                if (current_listener.data_size == 0) {
                    current_listener.resolve(Buffer.from([]));
                    current_listener = null;
                }
            } else {
                let input_len = data.length - current_byte;
                let num_unreceived_bytes = current_listener.data_size - current_listener.current_data.length;
                let read_amount = input_len < num_unreceived_bytes ? input_len : num_unreceived_bytes;
                for (let index = 0; index < read_amount; index++) {
                    current_listener.current_data.push(data[current_byte])
                    current_byte++;
                }
                if (read_amount == num_unreceived_bytes) {
                    current_listener.resolve(Buffer.from(current_listener.current_data));
                    current_listener = null;
                }
            }
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
    COMMAND_STOP: 'x'.charCodeAt(0),
    COMMAND_BEGIN_FILE: 'b'.charCodeAt(0),
    COMMAND_END_FILE: 'e'.charCodeAt(0),
    COMMAND_GET_FORMAT: 'c'.charCodeAt(0),
    COMMAND_GET_STREAM_LOD: 'L'.charCodeAt(0),
    COMMAND_SET_STREAM_LOD: 'l'.charCodeAt(0),
};