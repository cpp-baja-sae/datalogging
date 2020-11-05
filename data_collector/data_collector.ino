#include "file_io.h"
#include "tasks.h"
#include "util.h"

void setupOutputPin(const int pinNumber, const int value) {
  pinMode(pinNumber, OUTPUT);
  digitalWriteFast(pinNumber, value);
}

void setupPins() {
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
}

void setup() {
  setupSdCard();
  setupPins();
  FileBuffer test(23, 5);
  startTaskTimer();

  int counter = 0;
  while (counter < 1000) {
    if (multipleNewFramesError) {
      criticalError("ERROR: main loop took too long to read incoming data.");
    }

    if (nextUnreadFrameBufferIndex != currentWipFrameBufferIndex) {
      auto *ptr = &frameBuffers[nextUnreadFrameBufferIndex][0];
      auto constPtr = const_cast<const uint8_t*>(ptr);
      test.append(constPtr, FRAME_SIZE);
      counter += 1;
      while (test.writeSector());
      nextUnreadFrameBufferIndex = (nextUnreadFrameBufferIndex + 1) % NUM_FRAME_BUFFERS;
    }

    // We have received a command over USB...
    if (Serial.available()) {
      pauseTaskTimer();
      uint8_t command[2];
      for (int i = 0; i < 2; i++) {
        while (!Serial.available());
        command[i] = Serial.read();
      }
      uint8_t commandId == command[0] & 0xF0;
      // Read file.
      if (commandId == 0x00) {
        int slotIndex = command[1];
        int fileIndex = command[0] & 0x0F;
      }
      resumeTaskTimer();
    }
  }

  test.close();

  criticalError("Nothing else to do.");
}

void loop() {
}
