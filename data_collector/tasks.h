#ifndef TASKS_H_
#define TASKS_H_

// tasks.ino is responsible for recording data from sensors and placing it into
// frameBuffers to be processed by the rest of the code. The idea is that the
// interrupt should be allowed to run whenever possible such that data is
// recorded at a regular interval.

// This is set true when the task interrupt has written over data which was not
// yet read outside the interrupt..
extern volatile bool multipleNewFramesError;
// This is where data is stored.
extern volatile uint8_t frameBuffers[NUM_FRAME_BUFFERS][FRAME_SIZE];
// Which framebuffer the interrupt is writing to and the next one that the main
// loop will read from, respectively.
extern volatile int currentWipFrameBufferIndex, nextUnreadFrameBufferIndex;

// Starts a timer to call the task interrupt.
void startTaskTimer();
void pauseTaskTimer();
void resumeTaskTimer();

#endif /* TASKS_H_ */
