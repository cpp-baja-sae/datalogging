#include "file_io.h"
#include "tasks.h"
#include "serial_commands.h"
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
  initialFormattingSetup();
  Serial.begin(9600);
  while (!Serial);
  startTaskTimer();

  while (true) {
    handleNewData();
    handleWaitingCommands();
  }

  criticalError("Nothing else to do.");
}

void loop() {
}
