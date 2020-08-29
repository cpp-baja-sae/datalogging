#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "config.h"
#include "workers.h"

void run_command(
    char command, 
    char *message, 
    int message_length, 
    char **response, 
    int *response_length
) {
    *response_length = IPC_RESPONSE_SIZE;
    *response = malloc(IPC_RESPONSE_SIZE);
    memset(*response, '\0', IPC_RESPONSE_SIZE);
    (*response)[0] = command;

    switch (command) {
    case IPC_COMMAND_STOP:
        printf("[SOCKET] Received stop command.\n");
        continue_flag = 0;
        break;
    case IPC_COMMAND_BEGIN_FILE:
        printf("[SOCKET] Received begin file command.\n");
        write_to_file_flag = 1;
        break;
    case IPC_COMMAND_END_FILE:
        printf("[SOCKET] Received end file command.\n");
        write_to_file_flag = 0;
        break;
    case IPC_COMMAND_GET_CONFIG:
        printf("[SOCKET] Received get config command.\n");
        // Response format:
        // 1: NUM_ADCS
        // 2: NUM_CHANNELS (per adc)
        // 3: 0x01 if currently writing to a file.
        // 4-5: stream_frame_interval
        (*response)[1] = NUM_ADCS;
        (*response)[2] = NUM_CHANNELS;
        (*response)[3] = write_to_file_flag;
        (*response)[4] = stream_frame_interval >> 8;
        (*response)[5] = stream_frame_interval % 0xFF;
        break;
    case IPC_COMMAND_SET_STREAM_INTERVAL:
        printf("[SOCKET] Received change stream interval command.\n");
        // 1 byte for command, 2 bytes for value to change to.
        if (message_length == 3) {
            stream_frame_interval = message[1] << 8 | message[2];
        } else {
            printf(
                "[SOCKET] Error, message length must be 3 for this command.\n"
            );
        }
        break;
    default:
        printf("[SOCKET] Invalid IPC command: %c.\n", command);
        break;
    }
}

void *command_worker(void *args) {
    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("[SOCKET] Failed to create socket.\n");
        exit(1);
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr)); // Clear everything.
    addr.sun_family = AF_UNIX; // Local Unix socket, not an inet socket.
    // Set the socket's path to be IPC_ID.
    strncpy(addr.sun_path, IPC_ID, sizeof(addr.sun_path) - 1);
    // Unbind any existing socket. This is bad practice if more than one
    // instance of the application is running at a time, but we won't be doing
    // that.
    unlink(IPC_ID);
    // Bind the socket that was created to the address we just specified.
    int result = bind(socket_fd, (struct sockaddr*) &addr, sizeof(addr));
    if (result < 0) {
        printf("[SOCKET] Failed to bind socket, error code %i.\n", errno);
        exit(1);
    }
    
    // Allow up to 5 clients to wait to connect.
    if (listen(socket_fd, 5) < 0) {
        printf("[SOCKET] Failed to listen(), error code %i.\n", errno);
        exit(1);
    }

    printf("[SOCKET] Setup complete.\n");

    char buffer[1];
    while (continue_flag) {
        struct sockaddr_un client_addr;
        int addr_len = sizeof(client_addr);
        printf("[SOCKET] Waiting for connection.\n");
        int client_fd = accept(
            socket_fd, 
            (struct sockaddr*) 
            &client_addr, 
            &addr_len
        );
        if (client_fd < 0) {
            printf("[SOCKET] Bad connection attempt, error code %i.\n", errno);
            // This is a recoverable error.
            continue;
        }
        printf("[SOCKET] Accepted an incoming connection.\n");
        while (continue_flag) {
            // The first byte is the length of the message.
            char length = '\0';
            int result = read(client_fd, &length, 1);
            if (result < 0) {
                printf("[SOCKET] Could not read message from client, ");
                printf("error code %i.\n", errno);
                // The client may have disconnected. Try to connect to a new
                // client.
                break;
            }
            int ilength = (int) length;
            if (ilength <= 0) {
                printf("[SOCKET] Messages cannot be zero bytes long.\n");
                // It is possible the client disconnected.
                break;
            }

            char *message = (char*) malloc(ilength);
            int real_length = read(client_fd, message, ilength);
            if (real_length < 0) {
                printf("[SOCKET] Could not read message from client, ");
                printf("error code %i.\n", errno);
                free(message);
                break;
            }
            if (real_length != ilength) {
                printf(
                    "[SOCKET] Expected %i bytes, but got %i bytes.\n",
                    ilength,
                    real_length
                );
                free(message);
                continue;
            }

            // First byte of the message is which command to use.
            char command = message[0];
            char *response;
            int response_length;
            run_command(command, message, ilength, &response, &response_length);

            if (write(client_fd, response, response_length) < 0) {
                printf(
                    "[SOCKET] Failed to send response, error code %i.\n",
                    errno
                );
                free(message);
                free(response);
                break;
            }
            free(message);
            free(response);
        }
        close(client_fd);
    }

    if (close(socket_fd) < 0) {
        printf("[SOCKET] Unable to close socket, error code %i.\n", errno);
        return NULL;
    } 
    if (unlink(IPC_ID) < 0) {
        printf("[SOCKET] Unable to unlink socket, error code %i.\n", errno);
        return NULL;
    } 
    printf("[SOCKET] Successfully cleaned up socket.\n");
}