IntervalTimer testTimer;

// 64 bytes are transmitted every frame.
#define STEPS_PER_FRAME 64

void setup() {
    // We light up the onboard LED if there is an error.
    pinMode(13, OUTPUT);
    digitalWriteFast(13, LOW);
    // For error messages.
    Serial.begin(9600);

    testTimer.begin(onStepClockReceived, 50000);
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
        digitalWriteFast(13, HIGH);
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
    delay(49);
    endStep();
}

