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
    rawSPI_t info = {
        .clk = PIN_SCLK,
        .mosi = PIN_UNUSED,
        .ss_pol = 1, // Resting value for the slave select pin.
        .ss_us = 1, // How long to wait after switching the slave select value.
        .clk_pol = 0, // Resting value for the clock pin.
        .clk_pha = 0, // 0 indicates sample on 1st clock edge, 1 indicates 2nd edge.
        .clk_us = 1, // Microseconds between clock pulses.
    };

    int time_offset = 0;
    for (int cycle = 0; cycle < GPIO_BUFFER_LEN; cycle++) {
        char data_buf[NUM_CHANNELS * 2 + 1];
        for (int i = 0; i < NUM_CHANNELS * 2; i++) {
            data_buf[i] = 0xFF;
        }
        // Read every value, 16 bits per value.
        int rbits = NUM_CHANNELS * 16;
        int tbits = rbits;
        // Generates a waveform which requests data from the SPI bus.
        rawWaveAddSPI(
            &info,   // Information about which pins to set.
            time_offset, // When to start sending the waveform.
            PIN_CS,      // Which slave select pin to use.
            data_buf,    // What data to send.
            tbits,       // How many bits to write from the buffer.
            0,           // Which received bit to start storing.
            rbits,       // Which received bit to stop storing on.
            tbits        // Overall, how many bits to read (with/out storing).
        );

        // 16 bits per channel, 1 clock cycle per bit, 2us per clock cycle.
        // Add some extra delay for stability.
        int read_time = (NUM_CHANNELS * 16 * 2) + 6;

        gpioPulse_t convst_signal[8];
        convst_signal[0].gpioOn  = 0;
        convst_signal[0].gpioOff = 0;
        convst_signal[0].usDelay = time_offset;

        convst_signal[1].gpioOn  = 1 << PIN_CONVST;
        convst_signal[1].gpioOff = 0;
        convst_signal[1].usDelay = read_time;

        convst_signal[2].gpioOn  = 0;
        convst_signal[2].gpioOff = 1 << PIN_CONVST;
        convst_signal[2].usDelay = 8;

        convst_signal[3].gpioOn  = 1 << PIN_CONVST;
        convst_signal[3].gpioOff = 0;
        convst_signal[3].usDelay = FRAME_TIME - 8 - read_time;
        gpioWaveAddGeneric(4, convst_signal);

        // gpioPulse_t reset_signal[8];
        // reset_signal[0].gpioOn  = 0;
        // reset_signal[0].gpioOff = 0;
        // reset_signal[0].usDelay = time_offset;

        // reset_signal[1].gpioOn = 0;
        // reset_signal[1].gpioOff  = 1 << PIN_RESET;
        // reset_signal[1].usDelay = read_time;

        // reset_signal[2].gpioOn = 1 << PIN_RESET;
        // reset_signal[2].gpioOff  = 0;
        // reset_signal[2].usDelay = 8;

        // reset_signal[3].gpioOn = 0;
        // reset_signal[3].gpioOff  = 1 << PIN_RESET;
        // reset_signal[3].usDelay = FRAME_TIME - 8 - read_time;
        // gpioWaveAddGeneric(4, reset_signal);
    
        time_offset += FRAME_TIME;
    }

    // These two pulses do nothing for FRAME_TIME * GPIO_BUFFER_LEN microseconds.
    // This ensures that there is still a delay after the last transaction
    // before the whole waveform starts over again.
    gpioPulse_t end_padding[2];
    end_padding[0].gpioOn = 0;
    end_padding[0].gpioOff  = 0;
    end_padding[0].usDelay = time_offset;
    // This second pulse is necessary to make the first delay actually occur.
    end_padding[1].gpioOn = 0;
    end_padding[1].gpioOff  = 0;
    end_padding[1].usDelay = 0;
    gpioWaveAddGeneric(2, end_padding);

    int wave_id = gpioWaveCreate();
    if (wave_id < 0) {
        printf("[SENSOR] Failed to create waveform! Try reducing ");
        printf("NUM_BATCHES.\n");
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
    while (continue_flag) {
        int current_cycle_in_progress 
            = (rawWaveCB() - bottom_cb) / cbs_per_cycle % GPIO_BUFFER_LEN;

        int cycles_read = 0;
        while (reading_from != current_cycle_in_progress) {
            int current_ool = top_ool - reading_from * FRAME_SIZE;

            for (int index = 0; index < FRAME_SIZE; index++) {
                uint32_t pin_values = rawWaveGetOut(current_ool);
                primary_file_buffer[pbuf_write_index + index]
                    = (pin_values >> TEENSY_FIRST_DATA_PIN) & 0xFF;
                current_ool--;
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