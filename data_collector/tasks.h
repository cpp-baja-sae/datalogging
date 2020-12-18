#ifndef TASKS_H_
#define TASKS_H_

#include "util.h"

// tasks.ino is responsible for recording data from sensors and placing it into
// frameBuffers to be processed by the rest of the code. The idea is that the
// interrupt should be allowed to run whenever possible such that data is
// recorded at a regular interval.

// This struct must contain NO GAPS between its members due to alignment.
// https://stackoverflow.com/questions/6242006/struct-member-alignment-is-it-possible-to-assume-no-padding
// https://developer.arm.com/documentation/dui0472/g/compiler-coding-practices/compiler-storage-of-data-objects-by-natural-byte-alignment?lang=en
struct DataFrame {
    int16_t adcReadings[4][8]; // 4 ADCs with 8 channels each.
    uint8_t errorCount;        // How many errors have occured so far.
    uint8_t lastErrorCode;     // A code for what caused the most recent error.
};

// This is set true when the task interrupt has written over data which was not
// yet read outside the interrupt..
extern volatile bool multipleNewFramesError;
// This is where data is stored.
extern volatile DataFrame frameBuffers[NUM_FRAME_BUFFERS];
// Which framebuffer the interrupt is writing to and the next one that the main
// loop will read from, respectively.
extern volatile int currentWipFrameBufferIndex, nextUnreadFrameBufferIndex;

// Starts a timer to call the task interrupt.
void startTaskTimer();
void pauseTaskTimer();
void resumeTaskTimer();

#endif /* TASKS_H_ */
