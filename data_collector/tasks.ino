#include "file_io.h"
#include "util.h"

IntervalTimer taskTimer;

volatile int currentTaskIndex = 0;
volatile bool multipleNewFramesError = false;
volatile DataFrame frameBuffers[NUM_FRAME_BUFFERS];
// Which framebuffer the interrupt is writing to and the next one that the main
// loop will read from, respectively.
volatile int currentWipFrameBufferIndex = 0, nextUnreadFrameBufferIndex = 0;

void startTaskTimer() {
  if (!taskTimer.begin(taskInterrupt, TASK_INTERVAL_US)) {
    criticalError("Failed to start taskInterrupt timer.");
  }
}

void pauseTaskTimer() {
  taskTimer.end();
}

void resumeTaskTimer() {
  pauseTaskTimer();
  startTaskTimer();
}

// Reads values from four ADCs whose pins are specified in util.h. To read all
// the data from the ADCs, first set chip select low, then do readAdcs(0), 2, 4,
// and 6 to get all the data out of the ADC, then raise CS high.
void startAdcRead() {
  digitalWriteFast(PIN_ADCS_CS, LOW);
}

void readAdcData(int channel) {
  uint8_t bitReads[16];
  for (int bit = 15; bit >= 0; bit--) {
      DELAY_25NS;
      digitalWriteFast(PIN_ADCS_SCLK, LOW);
      bitReads[bit] = (GPIO6_DR >> 16) & 0xFF;
      DELAY_25NS;
      digitalWriteFast(PIN_ADCS_SCLK, HIGH);
  }

  // 0a, 0b, 1a, 1b, etc.
  uint16_t values[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  for (int bit = 0; bit < 16; bit++) {
      for (int valueIndex = 0; valueIndex < 8; valueIndex++) {
          values[valueIndex] |= ((bitReads[bit] >> valueIndex) & 0x1) << bit;
      }
  }

  auto dataTarget = &frameBuffers[currentWipFrameBufferIndex];

  for (uint32_t adc = 0; adc < 4; adc++) {
    dataTarget->adcReadings[adc][channel] = values[adc * 2];
    dataTarget->adcReadings[adc][channel + 4] = values[adc * 2 + 1];
  }
}

void endAdcRead() {
  digitalWriteFast(PIN_ADCS_CS, HIGH);
}

// Tells the ADCs to start capturing new data.
void triggerAdcs() {
  DELAY_25NS;
  digitalWriteFast(PIN_ADCS_RESET, HIGH);
  digitalWriteFast(PIN_ADCS_CONVST, LOW);
  DELAY_25NS;
  DELAY_25NS;
  digitalWriteFast(PIN_ADCS_RESET, LOW);
  DELAY_25NS;
  digitalWriteFast(PIN_ADCS_CONVST, HIGH);
}

// Called 10k times per second, based on TASK_INTERVAL_US. Called 20 times per
// data frame, based on TASKS_PER_FRAME.
void taskInterrupt() {
  if (currentTaskIndex == 0) startAdcRead();
  if (currentTaskIndex < 4) {
    readAdcData(currentTaskIndex * 2);
  }
  if (currentTaskIndex == 4) {
    endAdcRead();
    triggerAdcs();
  }

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