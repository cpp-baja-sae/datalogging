#include "generated/config.h"
#include "file_io.h"
#include "formatting.h"
#include "util.h"

struct LodBuffer {
    uint8_t minBuffer[FRAME_SIZE];
    uint8_t maxBuffer[FRAME_SIZE];
    uint8_t avgBuffer[FRAME_SIZE];
    // How many samples have accumulated in this buffer so far.
    int progress;
    // Whether or not the file buffer should be written to.
    bool writeToBuffer;
    FileBuffer fileBuffer;
};

LodBuffer lodBuffers[NUM_LOW_RES_LODS];

// By default, the Arduino IDE does not compile this file, so we force it to be
// part of this.
#include "generated/data_ops.cpp"

void initialFormattingSetup() {

}
