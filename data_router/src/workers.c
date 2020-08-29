#include "workers.h"

volatile int continue_flag = 1;
volatile int write_to_file_flag = 1;
volatile int stream_frame_interval = 100;

volatile int pbuf_write_index = 0;
volatile char primary_file_buffer[FILE_BUFFER_SIZE];
volatile struct LodInfo lod_infos[NUM_AUX_LODS];