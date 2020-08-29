#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "workers.h"

void interrupt_handler(int _) {
    continue_flag = 0;
}

void reset_lod_buffer(int lod_index) {
    lod_infos[lod_index].progress = 0;
    for (int val_index = 0; val_index < FRAME_LEN; val_index++) {
        lod_infos[lod_index].min_buffer[val_index] = 0xFFFF;
        lod_infos[lod_index].max_buffer[val_index] = 0;
        lod_infos[lod_index].avg_buffer[val_index] = 0;
    }
}

void initialize_gpio() {
    gpioSetMode(PIN_CS, PI_OUTPUT);
    gpioSetMode(PIN_SCLK, PI_OUTPUT);
    gpioSetMode(PIN_CONVST, PI_OUTPUT);
    gpioSetMode(PIN_RESET, PI_OUTPUT);

    gpioWrite(PIN_RESET, 0);
    usleep(20);
    gpioWrite(PIN_RESET, 1);
    usleep(20);
    gpioWrite(PIN_RESET, 0);
}

void initialize() {
    // Ensure that all these values are initialized correctly without garbage
    // values.
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

    if (gpioInitialise() < 0) {
        printf("[SENSOR] Failed to initialize GPIO! Make sure you are ");
        printf("with sudo.\n");
        exit(1);
    }

    initialize_gpio();

    gpioSetSignalFunc(SIGINT, interrupt_handler);

    printf("[SENSOR] Successfully initialized GPIO.\n");
}

void commit_lod(int lod_index) {
    // Actually average the averages.
    // We wait to do this step until after we have written every value because
    // it gives us higher precision.
    volatile struct LodInfo *this_lod = &lod_infos[lod_index];
    for (int val_index = 0; val_index < FRAME_LEN; val_index++) {
        (*this_lod).avg_buffer[val_index] /= LOD_SAMPLE_INTERVAL;
    }
    // If this is not the highest-level LOD, then update the next LOD's min, max, and avg.
    if (lod_index < NUM_AUX_LODS - 1) {
        volatile struct LodInfo *next_lod = &lod_infos[lod_index + 1];
        for (int val_index = 0; val_index < FRAME_LEN; val_index++) {
            if (this_lod->min_buffer[val_index] < next_lod->min_buffer[val_index]) {
                next_lod->min_buffer[val_index] = this_lod->min_buffer[val_index];
            }
            if (this_lod->max_buffer[val_index] > next_lod->max_buffer[val_index]) {
                next_lod->max_buffer[val_index] = this_lod->max_buffer[val_index];
            }
            next_lod->avg_buffer[val_index] += this_lod->avg_buffer[val_index];
        }
        next_lod->progress += 1;
        if (next_lod->progress == LOD_SAMPLE_INTERVAL) {
            commit_lod(lod_index + 1);
        }
    }
    // Write new values to file buffer. We have to separate them into three frames to make sure
    // it writes correctly to the file buffer. The file buffer size is a multiple of two, but it
    // is not a multiple of six, so we cannot write them all at once.
    for (int val_index = 0; val_index < FRAME_LEN; val_index++) {
        int write_index = (*this_lod).fbuf_write_index;
        (*this_lod).file_buffer[write_index + 0] = (*this_lod).min_buffer[val_index] >> 8;
        (*this_lod).file_buffer[write_index + 1] = (*this_lod).min_buffer[val_index] & 0xFF;
        (*this_lod).fbuf_write_index = (write_index + 2) % FILE_BUFFER_SIZE;
    }
    for (int val_index = 0; val_index < FRAME_LEN; val_index++) {
        int write_index = (*this_lod).fbuf_write_index;
        (*this_lod).file_buffer[write_index + 0] = (*this_lod).max_buffer[val_index] >> 8;
        (*this_lod).file_buffer[write_index + 1] = (*this_lod).max_buffer[val_index] & 0xFF;
        (*this_lod).fbuf_write_index = (write_index + 2) % FILE_BUFFER_SIZE;
    }
    for (int val_index = 0; val_index < FRAME_LEN; val_index++) {
        int write_index = (*this_lod).fbuf_write_index;
        (*this_lod).file_buffer[write_index + 0] = (*this_lod).avg_buffer[val_index] >> 8;
        (*this_lod).file_buffer[write_index + 1] = (*this_lod).avg_buffer[val_index] & 0xFF;
        (*this_lod).fbuf_write_index = (write_index + 2) % FILE_BUFFER_SIZE;
    }
    // Reset the buffer to a state where new values can be written to it.
    reset_lod_buffer(lod_index);
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
    for (int cycle = 0; cycle < ADC_FRAME_BUFFER_LEN; cycle++) {
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
        convst_signal[3].usDelay = CYCLE_TIME - 8 - read_time;
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
        // reset_signal[3].usDelay = CYCLE_TIME - 8 - read_time;
        // gpioWaveAddGeneric(4, reset_signal);
    
        time_offset += CYCLE_TIME;
    }

    // These two pulses do nothing for CYCLE_TIME * ADC_FRAME_BUFFER_LEN microseconds.
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
    int cbs_per_cycle = num_cbs / ADC_FRAME_BUFFER_LEN;

    // OOLs (no idea what it stands for) store values read from pins. Each
    // OOL stores a 32-bit field containing the value of every GPIO pin at
    // the time it was captured. There are 10 OOLs for each cycle since we
    // are capturing 10 bits every cycle. OOLs are allocated from the top down,
    // so the top OOL corresponds to the first bit of the first read.
    int top_ool = waveform_info.topOOL;

    gpioWaveTxSend(waveform_id, PI_WAVE_MODE_REPEAT);

    int reading_from = 0;
    int values[NUM_ADCS * NUM_CHANNELS];
    while (continue_flag) {
        int current_cycle_in_progress 
            = (rawWaveCB() - bottom_cb) / cbs_per_cycle % ADC_FRAME_BUFFER_LEN;

        int cycles_read = 0;
        while (reading_from != current_cycle_in_progress) {
            for (int c = 0; c < NUM_ADCS * NUM_CHANNELS; c++) {
                values[c] = 0;
            }

            int current_ool = top_ool - reading_from * NUM_CHANNELS * 16;

            // Take the bit which represents what value the pin had and
            // turn it into the corresponding bit for the output value.
            // (E.G. the third bit of the value will appear in the third
            // value on pin 15, necessitating a right-shift of 12.)
            // TODO: Are we not using DOUTB?
            #define STORE_BIT(ADC_INDEX) \
                if (PIN_DOUTA##ADC_INDEX >= bit) { \
                    values[ADC_INDEX + channel * NUM_ADCS] |= \
                        (pin_values & (1 << PIN_DOUTA##ADC_INDEX))  \
                        >> (PIN_DOUTA##ADC_INDEX - bit); \
                } else { \
                    values[ADC_INDEX + channel * NUM_ADCS] |= \
                        (pin_values & (1 << PIN_DOUTA##ADC_INDEX))  \
                        << (bit - PIN_DOUTA##ADC_INDEX); \
                }
            for (int channel = 0; channel < NUM_CHANNELS; channel++) {
                // For centuries, philosophers have pondered the great questions
                // of the universe:
                // - What is the meaning of life?
                // - Where did the universe come from?
                // - Why does this if statement make everything work correctly?
                if (channel == 0)
                    current_ool--;
                else if (channel == 1)
                    current_ool++;
                for (int bit = 15; bit >= 0; bit--) {
                    uint32_t pin_values = rawWaveGetOut(current_ool);
                    FOR_EVERY_ADC(STORE_BIT)
                    current_ool--;
                }
            }
            #undef STORE_BIT

            for (int channel = 0; channel < NUM_CHANNELS; channel++) {
                for (int adc = 0; adc < NUM_ADCS; adc++) {
                    int value = values[adc + channel * NUM_ADCS];
                    if (adc == 1 && channel == 6) {
                        printf("%i\n", value);
                    }
                    primary_file_buffer[pbuf_write_index] = (value & 0xFF00) >> 8;
                    primary_file_buffer[pbuf_write_index + 1] = value & 0x00FF;
                    pbuf_write_index = (pbuf_write_index + 2) % FILE_BUFFER_SIZE;

                    int lbuf_index = adc * NUM_CHANNELS + channel;
                    if (lod_infos[0].min_buffer[lbuf_index] > value) {
                        lod_infos[0].min_buffer[lbuf_index] = value;
                    }
                    if (lod_infos[0].max_buffer[lbuf_index] < value) {
                        lod_infos[0].max_buffer[lbuf_index] = value;
                    }
                    lod_infos[0].avg_buffer[lbuf_index] += value;
                }
            }

            lod_infos[0].progress += 1;
            // If we have written enough samples to the first LOD...
            if (lod_infos[0].progress == LOD_SAMPLE_INTERVAL) {
                // Save the information and propogate it up to higher LODs
                // as necessary.
                commit_lod(0);
            }

            reading_from = (reading_from + 1) % ADC_FRAME_BUFFER_LEN;
            cycles_read += 1;
        }
        if (cycles_read > ADC_FRAME_BUFFER_LEN / 2 + ADC_FRAME_BUFFER_LEN / 4) {
            printf(
                "[SENSOR] WARNING: Data buffer was pretty full. (%i/%i)\n",
                cycles_read, ADC_FRAME_BUFFER_LEN 
            );
        }
        usleep(500);
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