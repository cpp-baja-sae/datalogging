#include <time.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"
#include "workers.h"

FILE *primary_file;
int pbuf_read_index = 0;

void begin_data_log_file() {
    printf("[WRITER] Starting new file.\n");

    uint64_t timestamp = (uint64_t) time(NULL);
    // 400 is kind of overkill, just being safe.
    char folder_name[400], file_name[400]; 
    sprintf(folder_name, "%s/datalog_%.20lli", OUTPUT_DIR, timestamp);
    mkdir(folder_name, 0755);

    // Write format.
    sprintf(file_name, "%s/format.json", folder_name);
    FILE *format_file = fopen(file_name, "wb");
    fprintf(format_file, DEFAULT_FORMAT_CONTENT);
    fclose(format_file);

    // Open a file to write the primary info into.
    sprintf(file_name, "%s/0.bin", folder_name);
    primary_file = fopen(file_name, "wb");

    for (int lod = 0; lod < NUM_AUX_LODS; lod++) {
        // Open an additional file for each LOD.
        sprintf(file_name, "%s/%i.bin", folder_name, lod + 1);
        lod_infos[lod].target_file = fopen(file_name, "wb");
    }
}

// chunk_size must be a factor of FILE_BUFFER_SIZE
void write_new_data_to_file(
    volatile char *source, FILE *target, volatile int *read_index, int write_index, int chunk_size 
) {
    int unwritten_bytes;
    if (*read_index == write_index) {
        unwritten_bytes = 0;
    } else if (write_index > *read_index) {
        unwritten_bytes = write_index - *read_index;
    } else {
        // The write index has looped around to the start of the buffer.
        unwritten_bytes = FILE_BUFFER_SIZE - (*read_index - write_index);
    }
    if (unwritten_bytes > FILE_BUFFER_SIZE / 2) {
        printf(
            "[WRITER] WARNING: A file buffer is kind of full. (%i/%i)\n",
            unwritten_bytes, FILE_BUFFER_SIZE
        );
    }
    while (unwritten_bytes >= chunk_size) {
        // We can safely assume the data does not wrap around because the
        // size of the whole buffer is a multiple of chunk_size
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
        fwrite(&source[*read_index], chunk_size, 1, target);
        #pragma GCC diagnostic pop
        unwritten_bytes -= chunk_size;
        *read_index = (*read_index + chunk_size) % FILE_BUFFER_SIZE;
    }
}

void update_files() {
    write_new_data_to_file(
        primary_file_buffer, 
        primary_file, 
        &pbuf_read_index, 
        pbuf_write_index, 
        FILE_BLOCK_SIZE
    );
    for (int lod_index = 0; lod_index < NUM_AUX_LODS; lod_index++) {
        write_new_data_to_file(
            lod_infos[lod_index].file_buffer,
            lod_infos[lod_index].target_file,
            &lod_infos[lod_index].fbuf_read_index,
            lod_infos[lod_index].fbuf_write_index,
            lod_infos[lod_index].file_write_block_size
        );
    }
}

void *file_worker(void *args) {
    while (continue_flag) {
        // Every time write_to_file_flag is set, a new file is created.
        if (write_to_file_flag) {
            begin_data_log_file();
            // Skip to the most currently written frame.
            pbuf_read_index = pbuf_write_index;
            pbuf_read_index -= pbuf_read_index % FRAME_SIZE;
            while (continue_flag && write_to_file_flag) {
                update_files();
                usleep(50000);
            }
            printf("[WRITER] Closing files.\n");
            fclose(primary_file);
            for (int lod_index = 0; lod_index < NUM_AUX_LODS; lod_index++) {
                fclose(lod_infos[lod_index].target_file);
            }
        }
        sleep(1);
    }
    return NULL;
}