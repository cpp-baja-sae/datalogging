#include "file_io.h"
#include "util.h"

IntervalTimer taskTimer;

volatile int currentTaskIndex = 0;
volatile bool multipleNewFramesError = false;
volatile uint8_t frameBuffers[NUM_FRAME_BUFFERS][FRAME_SIZE];
// Which framebuffer the interrupt is writing to and the next one that the main
// loop will read from, respectively.
volatile int currentWipFrameBufferIndex = 0, nextUnreadFrameBufferIndex = 0;

void setupOutputPin(const int pinNumber, const int value) {
  pinMode(pinNumber, OUTPUT);
  digitalWriteFast(pinNumber, value);
}

void setup() {
  setupSdCard();

  setupOutputPin(PIN_ADCS_CS, HIGH);
  setupOutputPin(PIN_ADCS_SCLK, HIGH);
  setupOutputPin(PIN_ADCS_RESET, LOW);
  setupOutputPin(PIN_ADCS_CONVST, HIGH);

  pinMode(PIN_ADC0_DOUTA, INPUT_PULLUP);
  pinMode(PIN_ADC0_DOUTB, INPUT_PULLUP);
  pinMode(PIN_ADC1_DOUTA, INPUT_PULLUP);
  pinMode(PIN_ADC1_DOUTB, INPUT_PULLUP);
  pinMode(PIN_ADC2_DOUTA, INPUT_PULLUP);
  pinMode(PIN_ADC2_DOUTB, INPUT_PULLUP);
  pinMode(PIN_ADC3_DOUTA, INPUT_PULLUP);
  pinMode(PIN_ADC3_DOUTB, INPUT_PULLUP);

  FileBuffer test(23, 5);
  taskTimer.begin(taskInterrupt, TASK_INTERVAL_US);

  int counter = 0;
  while (counter < 1000) {
    if (multipleNewFramesError) {
      criticalError("ERROR: main loop took too long to read incoming data.");
    }

    if (nextUnreadFrameBufferIndex != currentWipFrameBufferIndex) {
      auto *ptr = &frameBuffers[nextUnreadFrameBufferIndex][0];
      auto const_ptr = const_cast<const uint8_t*>(ptr);
      test.append(const_ptr, FRAME_SIZE);
      counter += 1;
      while (test.writeSector());
      nextUnreadFrameBufferIndex = (nextUnreadFrameBufferIndex + 1) % NUM_FRAME_BUFFERS;
    }
  }

  test.close();

  criticalError("Nothing else to do.");
}

// Reads values from four ADCs whose pins are specified in util.h.
void readAdcs() {
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

  auto dataTarget = &frameBuffers[currentWipFrameBufferIndex][0];

  dataTarget[0 + 0] = values[0] & 0xFF;
  dataTarget[0 + 1] = values[0] >> 8;
  dataTarget[0 + 8] = values[1] & 0xFF;
  dataTarget[0 + 9] = values[1] >> 8;
  dataTarget[16 + 0] = values[2] & 0xFF;
  dataTarget[16 + 1] = values[2] >> 8;
  dataTarget[16 + 8] = values[3] & 0xFF;
  dataTarget[16 + 9] = values[3] >> 8;
  dataTarget[32 + 0] = values[4] & 0xFF;
  dataTarget[32 + 1] = values[4] >> 8;
  dataTarget[32 + 8] = values[5] & 0xFF;
  dataTarget[32 + 9] = values[5] >> 8;
  dataTarget[48 + 0] = values[6] & 0xFF;
  dataTarget[48 + 1] = values[6] >> 8;
  dataTarget[48 + 8] = values[7] & 0xFF;
  dataTarget[48 + 9] = values[7] >> 8;
}

// Called 10k times per second, based on TASK_INTERVAL_US. Called 20 times per
// data frame, based on TASKS_PER_FRAME.
void taskInterrupt() {
  // Sample analog data at the start of every frame.
  if (currentTaskIndex == 0) {
    readAdcs();
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

void loop() {
}
