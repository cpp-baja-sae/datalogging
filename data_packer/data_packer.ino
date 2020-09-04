#include <stdint.h>

IntervalTimer testTimer;

// 64 bytes are transmitted every frame.
#define STEPS_PER_FRAME 64

// This lights up when there is an error.
#define PIN_ONBOARD_LED 13

// Chip select pin
#define PIN_ADCS_CS 0
// Serial clock pin
#define PIN_ADCS_SCLK 1
#define PIN_ADCS_RESET 2
// Conversion start pin
#define PIN_ADCS_CONVST 3
// DOUTA and DOUTB pins for each ADC
#define PIN_ADC0_DOUTA 4
#define PIN_ADC0_DOUTB 5
#define PIN_ADC1_DOUTA 6
#define PIN_ADC1_DOUTB 7
#define PIN_ADC2_DOUTA 8
#define PIN_ADC2_DOUTB 9
#define PIN_ADC3_DOUTA 10
#define PIN_ADC3_DOUTB 11

// Pauses execution of the program for a single clock cycle
#define DELAY_CLOCK_CYCLE __asm__("nop\n")
// Pauses execution of the program for 3 clock cycles. Our clock runs at 600MHz,
// so this results in a 5ns delay.
#define DELAY_5NS DELAY_CLOCK_CYCLE; DELAY_CLOCK_CYCLE; DELAY_CLOCK_CYCLE
#define DELAY_10NS DELAY_5NS; DELAY_5NS
#define DELAY_15NS DELAY_5NS; DELAY_5NS; DELAY_5NS
#define DELAY_20NS DELAY_5NS; DELAY_5NS; DELAY_5NS; DELAY_5NS
#define DELAY_25NS DELAY_5NS; DELAY_5NS; DELAY_5NS; DELAY_5NS; DELAY_5NS

void setupOutputPin(int pinNumber, int value) {
    pinMode(pinNumber, OUTPUT);
    digitalWriteFast(pinNumber, value);
}

void setup() {
    setupOutputPin(PIN_ONBOARD_LED, LOW);

    setupOutputPin(PIN_ADCS_CS, HIGH);
    setupOutputPin(PIN_ADCS_SCLK, HIGH);
    setupOutputPin(PIN_ADCS_RESET, LOW);
    setupOutputPin(PIN_ADCS_CONVST, HIGH);

    // For error messages.
    Serial.begin(9600);
    delay(2000);

    testTimer.begin(onStepClockReceived, 5);
    endStep();
}

volatile bool stepClockReceived = false;
int currentStep = STEPS_PER_FRAME - 1;

void onStepClockReceived() {
    stepClockReceived = true;
}

// Put this after the code for each step. It waits for another clock signal from
// the Pi. Upon receiving it, the next byte of data is transmitted. If your step
// code took longer than it should have it will report an error.
void endStep() {
    // This means we already received a clock signal. We should have to wait for
    // it. If it's already here that means we're late.
    if (stepClockReceived) {
        digitalWriteFast(PIN_ONBOARD_LED, HIGH);
        Serial.print("ERROR: Step ");
        Serial.print(currentStep);
        Serial.print(" did not finish before the next step.\n");
        stepClockReceived = false;
    } else {
        while (!stepClockReceived) { }
    }
    stepClockReceived = false;
    currentStep = (currentStep + 1) % STEPS_PER_FRAME;
}

void loop() {
    {
        digitalWriteFast(PIN_ADCS_CS, LOW);
        uint16_t value0a = 0, value0b = 0, value1a = 0, value1b = 0, 
            value2a = 0, value2b = 0, value3a = 0, value3b = 0;
        for (int bit = 15; bit >= 0; bit--) {
            DELAY_25NS;
            digitalWriteFast(PIN_ADCS_SCLK, LOW);
            
            DELAY_25NS;
            digitalWriteFast(PIN_ADCS_SCLK, HIGH);
        }
        DELAY_25NS;
        digitalWriteFast(PIN_ADCS_CS, HIGH);
    }
    endStep();
    for (int step = 0; step < STEPS_PER_FRAME - 1 + 100 * STEPS_PER_FRAME; step++) {
        endStep();
    }
}

