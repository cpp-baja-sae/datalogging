#include <algorithm>
#include "generated_format_info.h"
#include "file_io.h"
#include "formatting.h"
#include "tasks.h"
#include "util.h"

struct LodBuffer {
  DataFrame minBuffer, maxBuffer, avgBuffer;
  // How many samples have accumulated in this buffer so far.
  int progress;
  FileBuffer fileBuffer;
};

bool fileBuffersOpen = false;
FileBuffer highResFileBuffer;
LodBuffer lodBuffers[NUM_LOW_RES_LODS];

// Called when a buffer should be reset so it behaves as if it has never
// recorded any samples. (Does not touch the file buffer.)
void resetBuffer(int index) {
  LodBuffer &lod = lodBuffers[index];
  lod.progress = 0;
  for (int adc = 0; adc < 4; adc++) {
    for (int channel = 0; channel < 8; channel++) {
      // Reset these values so they don't interfere with actual recorded data.
      // (For example, 0x7FFF is the highest value an int16_t can hold, meaning
      // that once we get actual data, it will correctly make the value go down
      // since it is supposed to store the minimum.)
      lod.minBuffer.adcReadings[adc][channel] = 0x7FFF;
      lod.maxBuffer.adcReadings[adc][channel] = -0x8000;
      lod.avgBuffer.adcReadings[adc][channel] = 0x0;
    }
  }
  lod.minBuffer.errorCount = 0;
  lod.maxBuffer.errorCount = 0;
  lod.avgBuffer.errorCount = 0;
  lod.minBuffer.lastErrorCode = 0;
  lod.maxBuffer.lastErrorCode = 0;
  lod.avgBuffer.lastErrorCode = 0;
}

// void onBufferProgressComplete(int index);

// This will update the provided LOD based on lower-resolution data. It is used
// both by onBufferProgressComplete and onNewData.
void updateLodBuffer(int targetIndex, DataFrame &minSrc, DataFrame &maxSrc, DataFrame &avgSrc) {
  LodBuffer &target = lodBuffers[targetIndex];
  // Calculate min/max/avg for ADC values.
  for (int adc = 0; adc < 4; adc++) {
    for (int channel = 0; channel < 8; channel++) {
      target.minBuffer.adcReadings[adc][channel] = std::min(
        target.minBuffer.adcReadings[adc][channel], 
        minSrc.adcReadings[adc][channel]
      );
      target.maxBuffer.adcReadings[adc][channel] = std::max(
        target.maxBuffer.adcReadings[adc][channel], 
        maxSrc.adcReadings[adc][channel]
      );
      target.avgBuffer.adcReadings[adc][channel] 
        += avgSrc.adcReadings[adc][channel] / LOD_SAMPLE_INTERVAL;
    }
  }
  // Calculate min/max/avg for diagnostics.
  target.minBuffer.errorCount += minSrc.errorCount;
  target.maxBuffer.errorCount += maxSrc.errorCount;
  target.avgBuffer.errorCount += avgSrc.errorCount;
  if (minSrc.lastErrorCode != 0) {
    target.minBuffer.lastErrorCode = minSrc.lastErrorCode;
    target.maxBuffer.lastErrorCode = maxSrc.lastErrorCode;
    target.avgBuffer.lastErrorCode = avgSrc.lastErrorCode;
  }

  target.progress += 1;
  // If our actions caused enough accumulation of samples, call 
  // onBufferProgressComplete() for target.
  if (target.progress == LOD_SAMPLE_INTERVAL) {
    onBufferProgressComplete(targetIndex);
  }
}

// Called when a buffer has accumulated LOD_SAMPLE_INTERVAL samples. It adds an
// additional sample to the LOD above it.
void onBufferProgressComplete(int index) {
  LodBuffer &thisLod = lodBuffers[index];
  if (index < NUM_LOW_RES_LODS - 1) {
    updateLodBuffer(index + 1, thisLod.minBuffer, thisLod.maxBuffer, thisLod.avgBuffer);
  }
  // Write min, max, and avg buffers to the corresponding file buffer in that order.
  if (fileBuffersOpen) {
    auto min = const_cast<const DataFrame&>(thisLod.minBuffer);
    auto max = const_cast<const DataFrame&>(thisLod.maxBuffer);
    auto avg = const_cast<const DataFrame&>(thisLod.avgBuffer);
    thisLod.fileBuffer.append(min);
    thisLod.fileBuffer.append(max);
    thisLod.fileBuffer.append(avg);
    while (thisLod.fileBuffer.writeSector());
    thisLod.fileBuffer.flushIfNeeded();
  }
  // Reset to prepare for a new batch of samples.
  resetBuffer(index);
}

// Called when a new max-res data frame has been processed.
void onNewData(DataFrame &frame) {
  updateLodBuffer(0, frame, frame, frame);
}

void beginNewDatalog(int slot) {
  if (fileBuffersOpen) endCurrentDatalog();
  deleteSlot(slot);
  saveDataFormat(slot, 15);
  highResFileBuffer = FileBuffer(slot, 0);
  int threshold = 512 * 1024; // Flush every 512 KiB
  highResFileBuffer.setFlushThreshold(threshold);
  for (int lodIndex = 0; lodIndex < NUM_LOW_RES_LODS; lodIndex++) {
    lodBuffers[lodIndex].fileBuffer = FileBuffer(slot, lodIndex + 1);
    lodBuffers[lodIndex].fileBuffer.setFlushThreshold(threshold);
    threshold /= LOD_SAMPLE_INTERVAL;
  }
  fileBuffersOpen = true;
}

void endCurrentDatalog() {
  if (!fileBuffersOpen) return;
  highResFileBuffer.close();
  for (int lod = 0; lod < NUM_LOW_RES_LODS; lod++) {
    lodBuffers[lod].fileBuffer.close();
  }
  fileBuffersOpen = false;
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
    onNewData(constRef);
    if (fileBuffersOpen) {
      highResFileBuffer.append(constRef);
      while (highResFileBuffer.writeSector());
      highResFileBuffer.flushIfNeeded();
    }
    nextUnreadFrameBufferIndex = (nextUnreadFrameBufferIndex + 1) % NUM_FRAME_BUFFERS;
  }
}
