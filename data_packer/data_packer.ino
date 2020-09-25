#include <stdint.h>

// NUMBERS SHOULD ALWAYS BE LITTLE-ENDIAN! This is because the Raspberry Pi does
// math in Little Endian, and I just lost multiple hours of debugging trying
// to figure out why a simple piece of code wasn't correctly computing the
// average of two (big-endian) numbers.

IntervalTimer testTimer;

// If defined, the program will use an internal clock instead of waiting for
// a clock on PIN_PICOM_CLOCK
// #define USE_TEST_TIMER
// How many milliseconds between steps (when using the test timer)
#define TEST_TIMER_PERIOD 5

// 100 bytes are transmitted every frame.
#define STEPS_PER_FRAME 100

// This lights up when there is an error.
#define PIN_ONBOARD_LED 13
// This pin goes high every time a step completes too late.
#define PIN_ERROR 4

// Chip select pin
#define PIN_ADCS_CS 0
// Serial clock pin
#define PIN_ADCS_SCLK 1
#define PIN_ADCS_RESET 2
// Conversion start pin
#define PIN_ADCS_CONVST 3
// DOUTA and DOUTB pins for each ADC. These pin numbers are selected so every
// pin can be read at once from GPIO6_DR (starting at bit 16)
// LSB
#define PIN_ADC0_DOUTA 19
#define PIN_ADC0_DOUTB 18
#define PIN_ADC1_DOUTA 14
#define PIN_ADC1_DOUTB 15
#define PIN_ADC2_DOUTA 40
#define PIN_ADC2_DOUTB 41
#define PIN_ADC3_DOUTA 17
// MSB
#define PIN_ADC3_DOUTB 16
// Pins for writing data to the Raspberry Pi. These pins are selected so that
// every pin can be written at once from GPIO6_DR (starting at bit 24)
// LSB
#define PIN_PICOM_0 22
#define PIN_PICOM_1 23
#define PIN_PICOM_2 20
#define PIN_PICOM_3 21
#define PIN_PICOM_4 38
#define PIN_PICOM_5 39
#define PIN_PICOM_6 26
// MSB
#define PIN_PICOM_7 27
// Clock from the Raspberry Pi signalling the start of the next step.
#define PIN_PICOM_CLOCK 33
// The Pi raises this line during the last clock signal of the frame. This is
// used to make sure we stay in sync with what the pi is expecting.
#define PIN_PICOM_LAST_STEP 34

// Pauses execution of the program for a single clock cycle
#define DELAY_CLOCK_CYCLE __asm__("nop\n")
// Pauses execution of the program for 3 clock cycles. Our clock runs at 600MHz,
// so this results in a 5ns delay.
#define DELAY_5NS                                                              \
    DELAY_CLOCK_CYCLE;                                                         \
    DELAY_CLOCK_CYCLE;                                                         \
    DELAY_CLOCK_CYCLE
#define DELAY_10NS                                                             \
    DELAY_5NS;                                                                 \
    DELAY_5NS
#define DELAY_15NS                                                             \
    DELAY_5NS;                                                                 \
    DELAY_5NS;                                                                 \
    DELAY_5NS
#define DELAY_20NS                                                             \
    DELAY_5NS;                                                                 \
    DELAY_5NS;                                                                 \
    DELAY_5NS;                                                                 \
    DELAY_5NS
#define DELAY_25NS                                                             \
    DELAY_5NS;                                                                 \
    DELAY_5NS;                                                                 \
    DELAY_5NS;                                                                 \
    DELAY_5NS;                                                                 \
    DELAY_5NS

int currentStep = STEPS_PER_FRAME - 1;

uint8_t dataBuffer1[STEPS_PER_FRAME], dataBuffer2[STEPS_PER_FRAME];
uint8_t *completedBuffer = &dataBuffer1[0], *wipBuffer = &dataBuffer2[0];

volatile bool stepClockReceived = false;
int lastBadStep = 0;
bool encounteredBadStep = false;

void onStepClockReceived() { stepClockReceived = true; }

// Put this after the code for each step. It waits for another clock signal from
// the Pi. Upon receiving it, the next byte of data is transmitted. If your step
// code took longer than it should have it will report an error.
void endStep() {
    // This means we already received a clock signal. We should have to wait for
    // it. If it's already here that means we're late.
    if (stepClockReceived) {
        stepClockReceived = false;
        digitalWriteFast(PIN_ONBOARD_LED, HIGH);
        // Don't overwrite an error we've already stored. Having a bad step can
        // easily lead to the next step being bad, obfuscating the real cause of
        // the error.
        if (!encounteredBadStep) {
            encounteredBadStep = true;
            lastBadStep = currentStep;
        }
        // Serial.print("ERROR: Step ");
        // Serial.print(currentStep);
        // Serial.print(" did not finish before the next step.\n");
    } else {
        digitalWriteFast(PIN_ERROR, LOW);
        while (!stepClockReceived) {
        }
        stepClockReceived = false;
    }
    // Set bits 24-32 of GPIO6_DR to the byte we want to transmit.
    // Unfortunately our microcontrollers have an internalized phobia of writing
    // multiple pins at the same time and end up causing erratic timing errors
    // as a coping mechanism. Instead we'll use a safer but more verbose method
    // until we can get a qualified electropsychologist to fix the problem.
    // Ideally the compiler will optimize all the writes into something with
    // performance similar to the original code.
    // GPIO6_DR = (GPIO6_DR & 0x00FFFFFF)
    // | (((uint32_t) completedBuffer[currentStep]) << 24);
    uint8_t valueToTransmit = completedBuffer[currentStep];
    digitalWriteFast(PIN_PICOM_0, valueToTransmit & 0x1 ? HIGH : LOW);
    digitalWriteFast(PIN_PICOM_1, valueToTransmit & 0x2 ? HIGH : LOW);
    digitalWriteFast(PIN_PICOM_2, valueToTransmit & 0x4 ? HIGH : LOW);
    digitalWriteFast(PIN_PICOM_3, valueToTransmit & 0x8 ? HIGH : LOW);
    digitalWriteFast(PIN_PICOM_4, valueToTransmit & 0x10 ? HIGH : LOW);
    digitalWriteFast(PIN_PICOM_5, valueToTransmit & 0x20 ? HIGH : LOW);
    digitalWriteFast(PIN_PICOM_6, valueToTransmit & 0x40 ? HIGH : LOW);
    digitalWriteFast(PIN_PICOM_7, valueToTransmit & 0x80 ? HIGH : LOW);
    currentStep = (currentStep + 1) % STEPS_PER_FRAME;
}

// Reads the next 16 bits of data from the ADCs. This function waits for 1 step
// in the middle.
void readAdcs(const int CHANNEL_OFFSET) {
    uint8_t bitReads[16];
    for (int bit = 15; bit >= 0; bit--) {
        DELAY_25NS;
        digitalWriteFast(PIN_ADCS_SCLK, LOW);
        bitReads[bit] = (GPIO6_DR >> 16) & 0xFF;
        DELAY_25NS;
        digitalWriteFast(PIN_ADCS_SCLK, HIGH);
    }

    endStep();

    // 0a, 0b, 1a, 1b, etc.
    uint16_t values[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (int bit = 0; bit < 16; bit++) {
        for (int valueIndex = 0; valueIndex < 8; valueIndex++) {
            values[valueIndex] |= ((bitReads[bit] >> valueIndex) & 0x1) << bit;
        }
    }

    // Little endian
    wipBuffer[CHANNEL_OFFSET + 0 + 0] = values[0] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 0 + 1] = values[0] >> 8;
    wipBuffer[CHANNEL_OFFSET + 0 + 8] = values[1] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 0 + 9] = values[1] >> 8;
    wipBuffer[CHANNEL_OFFSET + 16 + 0] = values[2] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 16 + 1] = values[2] >> 8;
    wipBuffer[CHANNEL_OFFSET + 16 + 8] = values[3] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 16 + 9] = values[3] >> 8;
    wipBuffer[CHANNEL_OFFSET + 32 + 0] = values[4] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 32 + 1] = values[4] >> 8;
    wipBuffer[CHANNEL_OFFSET + 32 + 8] = values[5] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 32 + 9] = values[5] >> 8;
    wipBuffer[CHANNEL_OFFSET + 48 + 0] = values[6] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 48 + 1] = values[6] >> 8;
    wipBuffer[CHANNEL_OFFSET + 48 + 8] = values[7] & 0xFF;
    wipBuffer[CHANNEL_OFFSET + 48 + 9] = values[7] >> 8;
}

// Called once before doCycle()
void reset() {
    // Wait to start receiving clock signals from the raspberry pi.
    endStep();
    endStep();
    endStep();
    // Keep consuming clock signals until we reach the last clock cycle of a
    // frame.
    while (true) {
        endStep();
        if (digitalReadFast(PIN_PICOM_LAST_STEP)) {
            currentStep = 0;
            break;
        }
    }
    // Since we were only trying to get in sync, an "error" just means we
    // started that process in the middle of a step, so nothing to worry about.
    encounteredBadStep = false;
    digitalWriteFast(PIN_ONBOARD_LED, LOW);
}

// Called over and over again until there is an error, at which point reset() is
// called and this resumes being called over and over again.
void doFrame() {
    { // Read ADCs, 8 steps
        digitalWriteFast(PIN_ADCS_CS, LOW);
        // readAdcs() uses an endStep() in the middle of it to break up its
        // calculations.
        readAdcs(0);
        endStep();
        readAdcs(2);
        endStep();
        readAdcs(4);
        endStep();
        readAdcs(6);
        DELAY_25NS;
        digitalWriteFast(PIN_ADCS_CS, HIGH);
        endStep();
    }
    { // Tell ADCs to read from inputs, 1 step.
        digitalWriteFast(PIN_ADCS_RESET, HIGH);
        digitalWriteFast(PIN_ADCS_CONVST, LOW);
        DELAY_25NS;
        DELAY_25NS;
        digitalWriteFast(PIN_ADCS_RESET, LOW);
        DELAY_25NS;
        digitalWriteFast(PIN_ADCS_CONVST, HIGH);
        endStep();
    }
    { // Debug output, 1 step.
        // Serial.println((int) wipBuffer[0]);
        // Serial.println((GPIO6_DR >> 16) & 0xFF, 2);
        endStep();
    }
    const int NUM_STEPS_USED = 10;
    // Wait for extra steps so that once we get back to the first one the
    // counter is correctly at zero.
    for (int step = 0; step < STEPS_PER_FRAME - NUM_STEPS_USED; step++) {
        endStep();
        // If we get this signal anytime we should immediately proceed back to
        // the start of the main loop. Without it everything still seems to be
        // robust and not drifting out of sync, so this is more of a just in
        // case a stray gamma ray hits something kind of thing.
        if (digitalReadFast(PIN_PICOM_LAST_STEP)) {
            currentStep = 0;
            break;
        }
    }
    // Swap buffers.
    {
        uint8_t *tmp = wipBuffer;
        wipBuffer = completedBuffer;
        completedBuffer = tmp;
    }
}

void setupOutputPin(const int pinNumber, const int value) {
    pinMode(pinNumber, OUTPUT);
    digitalWriteFast(pinNumber, value);
}

void setup() {
    setupOutputPin(PIN_ONBOARD_LED, LOW);

    setupOutputPin(PIN_ADCS_CS, HIGH);
    setupOutputPin(PIN_ADCS_SCLK, HIGH);
    setupOutputPin(PIN_ADCS_RESET, LOW);
    setupOutputPin(PIN_ADCS_CONVST, HIGH);
    setupOutputPin(PIN_ERROR, LOW);

    setupOutputPin(PIN_PICOM_0, LOW);
    setupOutputPin(PIN_PICOM_1, LOW);
    setupOutputPin(PIN_PICOM_2, LOW);
    setupOutputPin(PIN_PICOM_3, LOW);
    setupOutputPin(PIN_PICOM_4, LOW);
    setupOutputPin(PIN_PICOM_5, LOW);
    setupOutputPin(PIN_PICOM_6, LOW);
    setupOutputPin(PIN_PICOM_7, LOW);

    pinMode(PIN_ADC0_DOUTA, INPUT_PULLUP);
    pinMode(PIN_ADC0_DOUTB, INPUT_PULLUP);
    pinMode(PIN_ADC1_DOUTA, INPUT_PULLUP);
    pinMode(PIN_ADC1_DOUTB, INPUT_PULLUP);
    pinMode(PIN_ADC2_DOUTA, INPUT_PULLUP);
    pinMode(PIN_ADC2_DOUTB, INPUT_PULLUP);
    pinMode(PIN_ADC3_DOUTA, INPUT_PULLUP);
    pinMode(PIN_ADC3_DOUTB, INPUT_PULLUP);
    pinMode(PIN_PICOM_CLOCK, INPUT_PULLUP);
    pinMode(PIN_PICOM_LAST_STEP, INPUT_PULLUP);

    // Index 98 is error count, index 99 is last error cause.
    dataBuffer1[98] = 0;
    dataBuffer1[99] = 0xFF;
    dataBuffer2[98] = 0;
    dataBuffer2[99] = 0xFF;

    // For error messages.
    Serial.begin(115200);

#ifdef USE_TEST_TIMER
    testTimer.begin(onStepClockReceived, TEST_TIMER_PERIOD);
#else
    attachInterrupt(digitalPinToInterrupt(PIN_PICOM_CLOCK), onStepClockReceived,
                    RISING);
#endif
}

void loop() {
    reset();
    while (!encounteredBadStep) {
        doFrame();
    }
    // Index 98 is error count, index 99 is last error cause.
    dataBuffer1[98]++;
    dataBuffer1[99] = lastBadStep;
    dataBuffer2[98]++;
    dataBuffer2[99] = lastBadStep;

    encounteredBadStep = false;
    digitalWriteFast(PIN_ONBOARD_LED, LOW);
}
