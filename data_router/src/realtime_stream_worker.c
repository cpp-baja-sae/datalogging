#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "config.h"
#include "workers.h"

static int stream_index = 0;
static int old_stream_lod = DEFAULT_STREAM_LOD;

int send_unstreamed_data(int client_fd) {
    int write_index;
    if (stream_lod == 0) {
        write_index = pbuf_write_index;
    } else {
        write_index = lod_infos[stream_lod - 1].fbuf_write_index;
    }
    int frame_size;
    if (stream_lod == 0) {
        frame_size = FRAME_SIZE;
    } else {
        frame_size = FRAME_SIZE * 3;
    }
    volatile char *file_buffer;
    if (stream_lod == 0) {
        file_buffer = &primary_file_buffer[0];
    } else {
        file_buffer = &lod_infos[stream_lod - 1].file_buffer[0];
    }

    // If the requested stream LOD changed, we should reset pbuf_stream_index
    // because different LODs go through their buffers at different rates.
    if (old_stream_lod != stream_lod) {
        old_stream_lod = stream_lod;
        stream_index = write_index - (write_index % frame_size);
    }

    int unwritten_bytes;
    if (stream_index == write_index) {
        unwritten_bytes = 0;
    } else if (write_index > stream_index) {
        unwritten_bytes = write_index - stream_index;
    } else {
        // The write index has looped around to the start of the buffer.
        unwritten_bytes = FILE_BUFFER_SIZE - (stream_index - write_index);
    }
    if (unwritten_bytes > FILE_BUFFER_SIZE / 2) {
        printf("[STREAM] WARNING: Having troubles keeping up!\n");
    }

    while (unwritten_bytes >= frame_size) {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
        int result = write(client_fd, &file_buffer[stream_index], frame_size);
        if (result < 0) {
            // We failed to write, the client has probably disconnected.
            return 0;
        }
        stream_index = (stream_index + frame_size) % FILE_BUFFER_SIZE;
        #pragma GCC diagnostic pop
        unwritten_bytes -= frame_size;
    }

    return 1; // We are good to continue.
}

void *realtime_stream_worker(void *args) {
    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("[STREAM] Failed to create socket.\n");
        exit(1);
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, IPC_STREAM_ID, sizeof(addr.sun_path) - 1);
    unlink(IPC_STREAM_ID);
    int result = bind(socket_fd, (struct sockaddr*) &addr, sizeof(addr));
    if (result < 0) {
        printf("[STREAM] Failed to bind socket, error code %i.\n", errno);
        exit(1);
    }
    
    if (listen(socket_fd, 5) < 0) {
        printf("[STREAM] Failed to listen(), error code %i.\n", errno);
        exit(1);
    }

    printf("[STREAM] Setup complete.\n");

    while (continue_flag) {
        struct sockaddr_un client_addr;
        int addr_len = sizeof(client_addr);
        printf("[STREAM] Waiting for connection.\n");
        int client_fd = accept(
            socket_fd, 
            (struct sockaddr*) 
            &client_addr, 
            &addr_len
        );
        if (client_fd < 0) {
            printf("[STREAM] Bad connection attempt, error code %i.\n", errno);
            continue;
        }
        printf("[STREAM] Accepted an incoming connection.\n");
        // When send_unstreamed_data() sees that the "old lod" does not match
        // what the current lod is, it will reset the variables it uses to 
        // keep track of what data has not yet been streamed. Since we just got
        // a new connection, we need to do this because we have been sitting
        // around doing nothing while data piles up in the buffers we are 
        // reading from.
        old_stream_lod = -1;
        while (continue_flag && send_unstreamed_data(client_fd)) {
            usleep(1000);
        }
        close(client_fd);
    }

    if (close(socket_fd) < 0) {
        printf("[STREAM] Unable to close socket, error code %i.\n", errno);
        return NULL;
    } 
    if (unlink(IPC_STREAM_ID) < 0) {
        printf("[STREAM] Unable to unlink socket, error code %i.\n", errno);
        return NULL;
    } 
    printf("[STREAM] Successfully cleaned up socket.\n");
}