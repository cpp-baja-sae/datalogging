#ifndef WORKERS_H_
#define WORKERS_H_

#include <stdio.h>

#include "config.h"

struct LodInfo {
    char min_buffer[FRAME_SIZE];
    char max_buffer[FRAME_SIZE];
    char avg_buffer[FRAME_SIZE];
    // How many frames have been accumulated in the three buffers.
    int progress; 

    FILE *target_file;
    char file_buffer[FILE_BUFFER_SIZE];
    int fbuf_read_index;
    int fbuf_write_index;
    // LODs which have a lot of data will use a larger block size to be more
    // efficient. LODs which have less data will use a smaller block size to be
    // updated more often.
    int file_write_block_size;
};

extern volatile int continue_flag;
extern volatile int write_to_file_flag;
// Stream frames from this particular LOD.
extern volatile int stream_lod;

extern volatile int pbuf_write_index;
extern volatile char primary_file_buffer[FILE_BUFFER_SIZE];
extern volatile struct LodInfo lod_infos[NUM_AUX_LODS];

void *file_worker(void *args);
void *sensor_read_worker(void *args);
void *command_worker(void *args);
void *realtime_stream_worker(void *args);

#endif