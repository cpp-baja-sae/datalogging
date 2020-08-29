#ifndef CONFIG_H_
#define CONFIG_H_

//==============================================================================
// ADC-SPECIFIC CONSTANTS
//==============================================================================

#define PIN_CS 26      // GPIO pin for chip select.
#define PIN_SCLK 21    // GPIO pin for serial data clock.
#define PIN_CONVST 16  // GPIO pin for conversion start.
#define PIN_RESET 20   // GPIO pin for resetting all ADCs.
#define PIN_DOUTA0 2   // GPIO pin for DOUTA on ADC 0.
#define PIN_DOUTB0 4   // GPIO pin for DOUTB on ADC 0.
#define PIN_DOUTA1 17  // GPIO pin for DOUTA on ADC 1.
#define PIN_DOUTB1 22  // GPIO pin for DOUTB on ADC 1.
#define PIN_DOUTA2 10  // GPIO pin for DOUTA on ADC 2.
#define PIN_DOUTB2 11  // GPIO pin for DOUTB on ADC 2.
#define PIN_DOUTA3 0   // GPIO pin for DOUTA on ADC 3.
#define PIN_DOUTB3 6   // GPIO pin for DOUTB on ADC 3.
#define PIN_UNUSED 7

// Number of analog->digital converters.
#define NUM_ADCS 4      
// How many channels exist on each ADC.
#define NUM_CHANNELS 8  
#define ADC_DATA_LEN (NUM_ADCS * NUM_CHANNELS)
// 2 bytes for every value.
#define ADC_DATA_SIZE (ADC_DATA_LEN * 2) 
#define FOR_EVERY_ADC(MACRO) \
    MACRO(0) \
    MACRO(1) \
    MACRO(2) \
    MACRO(3) \
    // MACRO(4) \
    // MACRO(5) \
    // MACRO(6) \
    // MACRO(7) 

// Data received from the ADCs is stored in a ring buffer on one of the 
// raspberry pi's chips. This constant determines the length of that ring
// buffer. Increasing it makes the program more stable as it allows the program
// to be busy for longer before the buffer fills up. However, there is an upper
// limit to how big the buffer can be which is affected by a number of factors.
#define ADC_FRAME_BUFFER_LEN 16
// Delay in microseconds between each read operation.
#define CYCLE_TIME 500   

//==============================================================================
// GENERAL CONSTANTS
//==============================================================================

// How many data values are contained in each frame. Used for initializing 
// variables that keep track of mins, maxes, and averages.
#define FRAME_LEN (ADC_DATA_LEN)
// How many bytes each data frame occupies. FRAME_SIZE must be a factor of 
// FILE_BLOCK_SIZE
#define FRAME_SIZE (ADC_DATA_SIZE)
// Write to the file in 4k blocks.
#define FILE_BLOCK_SIZE 4096 
// I don't think the buffer needs to be this big but it's not really a problem.
#define FILE_BUFFER_SIZE (FRAME_SIZE * FILE_BLOCK_SIZE)
// How many additional versions of the file to create with sequentially lower
// resolutions.
#define NUM_AUX_LODS 7 
// How much the sample rate should be divided for each sequential file.
#define LOD_SAMPLE_INTERVAL 4

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
#define IPC_COMMAND_SET_STREAM_INTERVAL 'i'
// For simplicity's sake, we always send responses of a fixed size in response
// to messages received over the IPC socket.
#define IPC_RESPONSE_SIZE 32

// Must not end with a slash
#define OUTPUT_DIR "/root/datalogs"

#endif