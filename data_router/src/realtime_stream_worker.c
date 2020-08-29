#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "config.h"
#include "workers.h"

static int pbuf_stream_index = 0;

int send_unstreamed_data(int client_fd) {
    int sample_interval = stream_frame_interval * FRAME_SIZE;
    int unwritten_bytes;
    if (pbuf_stream_index == pbuf_write_index) {
        unwritten_bytes = 0;
    } else if (pbuf_write_index > pbuf_stream_index) {
        unwritten_bytes = pbuf_write_index - pbuf_stream_index;
    } else {
        // The write index has looped around to the start of the buffer.
        unwritten_bytes 
            = FILE_BUFFER_SIZE - (pbuf_stream_index - pbuf_write_index);
    }
    if (unwritten_bytes > FILE_BUFFER_SIZE / 4) {
        printf("[STREAM] WARNING: Having troubles keeping up!\n");
    }

    while (unwritten_bytes > sample_interval) {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
        int result 
            = write(client_fd, &primary_file_buffer[pbuf_stream_index], FRAME_SIZE);
        #pragma GCC diagnostic pop
        if (result < 0) {
            // We failed to write, the client has probably disconnected.
            return 0;
        }
        pbuf_stream_index 
            = (pbuf_stream_index + sample_interval) % FILE_BUFFER_SIZE;
        unwritten_bytes -= sample_interval;
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
        // Skip to the most currently written frame.
        pbuf_stream_index = pbuf_write_index;
        pbuf_stream_index -= pbuf_stream_index % FRAME_SIZE;
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