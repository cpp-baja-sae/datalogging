#include "file_io.h"
#include "util.h"

IntervalTimer taskTimer;

volatile int currentTaskIndex = 0;
volatile bool multipleNewFramesError = false;
volatile uint8_t frameBuffers[NUM_FRAME_BUFFERS][FRAME_SIZE];
// Which framebuffer the interrupt is writing to and the next one that the main
// loop will read from, respectively.
volatile int currentWipFrameBufferIndex = 0, nextUnreadFrameBufferIndex = 0;

void setup() {
  setupSdCard();

  FileBuffer test(23, 5);
  taskTimer.begin(taskInterrupt, TASK_INTERVAL_US);

  for (int n = 0; n < 100000; n++) {
    for (int i = 0; i < 100; i++) {
      test.append("Hello World!\n", 13);
    }

    while (test.writeSector()) {
      if (multipleNewFramesError) {
        criticalError("ERROR: recorded two or more data frames without the main loop pausing to store them.");
      }

      if (nextUnreadFrameBufferIndex != currentWipFrameBufferIndex) {
        // Do reading.
        nextUnreadFrameBufferIndex = (nextUnreadFrameBufferIndex + 1) % NUM_FRAME_BUFFERS;
      }
    }
  }
  test.close();

  criticalError("Nothing else to do.");
}

// Called 10k times per second, based on TASK_INTERVAL_US
void taskInterrupt() {
  currentTaskIndex += 1;
  if (currentTaskIndex == TASKS_PER_FRAME) {
    currentWipFrameBufferIndex = (currentWipFrameBufferIndex + 1) % NUM_FRAME_BUFFERS;
    if (currentWipFrameBufferIndex == nextUnreadFrameBufferIndex) {
      // We just wrote over a frame the main loop did not read yet.
      multipleNewFramesError = true;
    }
    currentTaskIndex = 0;
  }
}

void loop() {
}
