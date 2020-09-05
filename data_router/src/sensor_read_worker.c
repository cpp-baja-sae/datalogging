#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "workers.h"

#include "generated/data_ops.cpp"

void interrupt_handler(int _) {
    continue_flag = 0;
}

void initialize_gpio() {
    if (gpioInitialise() < 0) {
        printf("[SENSOR] Failed to initialize GPIO! Make sure you are ");
        printf("using sudo.\n");
        exit(1);
    }

    gpioSetMode(OSCILLOSCOPE_SYNC_PIN, PI_OUTPUT);
    gpioSetMode(TEENSY_STEP_CLOCK_PIN, PI_OUTPUT);
    for (int bit = 0; bit < 8; bit++) {
        gpioSetMode(TEENSY_FIRST_DATA_PIN + bit, PI_INPUT);
    }

    // Terminate the program when ^C is received.
    gpioSetSignalFunc(SIGINT, interrupt_handler);

    printf("[SENSOR] Successfully initialized GPIO.\n");
}

void initialize() {
    // Ensure that all these values are initialized correctly without garbage
    // values. LOD 0 does not need to be initialized because we just directly 
    // copy information into it without reading anything from it.
    for (int lod = 0; lod < NUM_AUX_LODS; lod++) {
        lod_infos[lod].progress = 0;
        lod_infos[lod].fbuf_read_index = 0;
        lod_infos[lod].fbuf_write_index = 0;
        reset_lod_buffer(lod);
    }
    // Set up the block sizes for each lod. LOD 6 writes about 1 frame every
    // second. 
    lod_infos[0].file_write_block_size = FILE_BLOCK_SIZE;
    lod_infos[1].file_write_block_size = FILE_BLOCK_SIZE;
    lod_infos[2].file_write_block_size = FILE_BLOCK_SIZE;
    lod_infos[3].file_write_block_size = FRAME_SIZE * 16;
    lod_infos[4].file_write_block_size = FRAME_SIZE * 4;
    lod_infos[5].file_write_block_size = FRAME_SIZE;
    lod_infos[6].file_write_block_size = FRAME_SIZE;

    initialize_gpio();
}

void use_realtime_priority() {
    pthread_t this_thread = pthread_self();
    struct sched_param params;
    params.sched_priority = sched_get_priority_max(SCHED_FIFO);
    int success = pthread_setschedparam(this_thread, SCHED_FIFO, &params);
    if (success != 0) {
        printf("[SENSOR] Failed to switch to realtime priority.\n");
        exit(1);
    }
    int policy = 0;
    success = pthread_getschedparam(this_thread, &policy, &params);
    if (success != 0 || policy != SCHED_FIFO) {
        printf("[SENSOR] Failed to switch to realtime priority.\n");
        exit(1);
    }
    printf("[SENSOR] Successfully switched to realtime priority.\n");
}

int create_tx_waveform() {
    gpioWaveAddNew();

    int time_offset = 0;
    for (int cycle = 0; cycle < GPIO_BUFFER_LEN; cycle++) {
        rawWave_t oscilloscope_signal[3];
        oscilloscope_signal[0].gpioOn = 0;
        oscilloscope_signal[0].gpioOff = 0;
        oscilloscope_signal[0].usDelay = time_offset;
        oscilloscope_signal[0].flags = 0;
        oscilloscope_signal[1].gpioOn = 1 << OSCILLOSCOPE_SYNC_PIN;
        oscilloscope_signal[1].gpioOff = 0;
        oscilloscope_signal[1].usDelay 
            = (STEP_CLOCK_ON_TIME + STEP_CLOCK_OFF_TIME) * FRAME_SIZE / 2;
        oscilloscope_signal[1].flags = 0;
        oscilloscope_signal[2].gpioOn = 0;
        oscilloscope_signal[2].gpioOff = 1 << OSCILLOSCOPE_SYNC_PIN;
        oscilloscope_signal[2].usDelay = 0;
        oscilloscope_signal[2].flags = 0;
        rawWaveAddGeneric(3, oscilloscope_signal);

        // Read FRAME_SIZE bytes in FRAME_SIZE steps.
        rawWave_t clock_signal[3];
        clock_signal[0].gpioOn = 0;
        clock_signal[0].gpioOff = 0;
        clock_signal[0].flags = 0;
        clock_signal[1].gpioOn = 1 << TEENSY_STEP_CLOCK_PIN;
        clock_signal[1].gpioOff = 0;
        clock_signal[1].usDelay = STEP_CLOCK_ON_TIME;
        clock_signal[1].flags = 0;
        clock_signal[2].gpioOn = 0;
        clock_signal[2].gpioOff = 1 << TEENSY_STEP_CLOCK_PIN;
        clock_signal[2].usDelay = STEP_CLOCK_OFF_TIME;
        clock_signal[2].flags = WAVE_FLAG_READ;
        for (int step = 0; step < FRAME_SIZE; step++) {
            clock_signal[0].usDelay = time_offset;
            rawWaveAddGeneric(3, clock_signal);
            time_offset += STEP_CLOCK_ON_TIME + STEP_CLOCK_OFF_TIME;
        }
    }

    // These two pulses do nothing for FRAME_TIME * GPIO_BUFFER_LEN microseconds.
    // This ensures that there is still a delay after the last step
    // before the whole waveform starts over again.
    rawWave_t end_padding[2];
    end_padding[0].gpioOn = 0;
    end_padding[0].gpioOff  = 0;
    end_padding[0].usDelay = time_offset;
    end_padding[0].flags = 0;
    // This second pulse is necessary to make the first delay actually occur.
    end_padding[1].gpioOn = 0;
    end_padding[1].gpioOff  = 0;
    end_padding[1].usDelay = 0;
    end_padding[0].flags = 0;
    rawWaveAddGeneric(2, end_padding);

    int wave_id = gpioWaveCreate();
    if (wave_id < 0) {
        printf("[SENSOR] Failed to create waveform! Try reducing ");
        printf("GPIO_BUFFER_LEN.\n");
        exit(1);
    }

    printf("[SENSOR] Successfully created waveform.\n");
    return wave_id;
}

void sensor_read_loop() {
    int waveform_id = create_tx_waveform();
    rawWaveInfo_t waveform_info = rawWaveInfo(waveform_id);

    // Control blocks store the output values of the waveform. By checking which
    // control block is currently in use, we can determine how far we have
    // progressed along the waveform. The lowest control block is the start, 
    // the highest is the end.
    int bottom_cb = waveform_info.botCB;
    int num_cbs = waveform_info.numCB;
    int cbs_per_cycle = num_cbs / GPIO_BUFFER_LEN;

    // OOLs (no idea what it stands for) store values read from pins. Each
    // OOL stores a 32-bit field containing the value of every GPIO pin at
    // the time it was captured. There are 10 OOLs for each cycle since we
    // are capturing 10 bits every cycle. OOLs are allocated from the top down,
    // so the top OOL corresponds to the first bit of the first read.
    int top_ool = waveform_info.topOOL;

    gpioWaveTxSend(waveform_id, PI_WAVE_MODE_REPEAT);

    int reading_from = 0;
    printf("%i %i\n", waveform_info.topCB, waveform_info.botCB);
    printf("%i %i\n", waveform_info.topOOL, waveform_info.botOOL);
    printf("%i %i\n", waveform_info.numTOOL, waveform_info.numBOOL);
    while (continue_flag) {
        int current_cycle_in_progress 
            = (rawWaveCB() - bottom_cb) / cbs_per_cycle % GPIO_BUFFER_LEN;

        int cycles_read = 0;
        while (reading_from != current_cycle_in_progress) {
            // The -1 is there to appease the ancient GPIO gods so that they may
            // bestow the blessings of functioning code upon us.
            int current_ool = top_ool - reading_from * FRAME_SIZE - 1;

            for (int index = 0; index < FRAME_SIZE; index++) {
                uint32_t pin_values = rawWaveGetOut(current_ool);
                primary_file_buffer[pbuf_write_index + index]
                    = (pin_values >> TEENSY_FIRST_DATA_PIN) & 0xFF;
                current_ool--;
            }

            if (reading_from == 0) {
                printf("%i\n", primary_file_buffer[pbuf_write_index]);
            }

            // This propogates the data we just wrote to the other LODs. Its 
            // code is automatically generated so that we don't have to manually
            // specify how each piece of data affects the min, max, and avg 
            // subframes of the next LOD.
            update_lods();

            pbuf_write_index 
                = (pbuf_write_index + FRAME_SIZE) % FILE_BUFFER_SIZE;

            reading_from = (reading_from + 1) % GPIO_BUFFER_LEN;
            cycles_read += 1;
        }
        if (cycles_read > GPIO_BUFFER_LEN / 2 + GPIO_BUFFER_LEN / 4) {
            printf(
                "[SENSOR] WARNING: Data buffer was pretty full. (%i/%i)\n",
                cycles_read, GPIO_BUFFER_LEN 
            );
        }
        usleep(100);
    }
}

void *sensor_read_worker(void *args) {
    // Change to realtime priority to ensure we can get sensor data as soon as it is available, and
    // avoid the tiny data buffer provided by the pi from filling up.
    use_realtime_priority();
    initialize();

    sensor_read_loop();

    gpioTerminate();
}