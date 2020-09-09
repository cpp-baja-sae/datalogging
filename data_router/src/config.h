#ifndef CONFIG_H_
#define CONFIG_H_

#include "generated/config.h"

// Data received from the Teensy is stored in a ring buffer on one of the 
// raspberry pi's chips. This constant determines the length of that ring
// buffer. Increasing it makes the program more stable as it allows the program
// to be busy for longer before the buffer fills up. However, there is an upper
// limit to how big the buffer can be which is affected by a number of factors.
#define GPIO_BUFFER_LEN 40

// Pins 5 through 12 are used to receive data from the Teensy.
#define TEENSY_FIRST_DATA_PIN 5
// The pin that triggers the Teensy to output the next byte (step).
#define TEENSY_STEP_CLOCK_PIN 24
// This pin is raised high during the last clock cycle of each frame to ensure
// the teensy stays in sync.
#define TEENSY_LAST_CLOCK_PIN 23

// When everything starts up, the LOD that should by default be streamed back
// in realtime.
#define DEFAULT_STREAM_LOD 3

// Write to the file in 4k blocks.
#define FILE_BLOCK_SIZE 4096 
#define FILE_BUFFER_SIZE (FRAME_SIZE * FILE_BLOCK_SIZE * 3)

// The name of the socket to be created to allow this program to talk to other
// programs on the pi, allowing it to be controlled from outside. This socket
// is used by the web server to change settings and check status. IPC stands
// for Inter-Process Communication.
#define IPC_ID "/tmp/.crunch_ipc"
// Same as above, but this socket is used to stream real-time data. Using two
// separate sockets simplifies communication protocols. The above socket mostly
// does small 32-byte long requests / responses, like a conversation. This
// socket just constantly yells data at whoever wants to listen.
#define IPC_STREAM_ID "/tmp/.crunch_stream"
#define IPC_COMMAND_STOP 'x'
#define IPC_COMMAND_BEGIN_FILE 'b'
#define IPC_COMMAND_END_FILE 'e'
#define IPC_COMMAND_GET_CONFIG 'c'
#define IPC_COMMAND_GET_STREAM_LOD 'L'
#define IPC_COMMAND_SET_STREAM_LOD 'l'
// For simplicity's sake, we always send responses of a fixed size in response
// to messages received over the IPC socket.
#define IPC_RESPONSE_SIZE 32

// Must not end with a slash
#define OUTPUT_DIR "/root/datalogs"

#endif