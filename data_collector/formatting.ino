#include "generated/config.h"
#include "file_io.h"
#include "formatting.h"
#include "tasks.h"
#include "util.h"

struct LodBuffer {
    DataFrame minBuffer, maxBuffer, avgBuffer;
    // How many samples have accumulated in this buffer so far.
    int progress;
    // Whether or not the file buffer should be written to.
    bool writeToBuffer;
    FileBuffer fileBuffer;
};

FileBuffer highResFileBuffer;
LodBuffer lodBuffers[NUM_LOW_RES_LODS];

// By default, the Arduino IDE does not compile this file, so we force it to be
// part of this.
#include "generated/data_ops.cpp"

void beginNewDatalog(int slot) {
    saveDataFormat(slot, 15);
    highResFileBuffer = FileBuffer(slot, 5);
}

void initialFormattingSetup() {
    beginNewDatalog(23);
}

void handleNewData() {
    if (multipleNewFramesError) {
      criticalError("ERROR: main loop took too long to read incoming data.");
    }

    while (nextUnreadFrameBufferIndex != currentWipFrameBufferIndex) {
      auto &nextFrame = frameBuffers[nextUnreadFrameBufferIndex];
      auto constRef = const_cast<const DataFrame&>(nextFrame);
      highResFileBuffer.append(constRef);
      while (highResFileBuffer.writeSector());
      highResFileBuffer.flushIfNeeded();
      nextUnreadFrameBufferIndex = (nextUnreadFrameBufferIndex + 1) % NUM_FRAME_BUFFERS;
    }
}
