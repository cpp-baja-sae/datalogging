#ifndef UTIL_H_
#define UTIL_H_

#include "generated/config.h"

// Contains miscellaneous code like settings and a ring buffer class. Some
// settings are provided by generated/config.h as they are derived from
// data_format.json.

// After 20 tasks have been performed, a frame should be saved to a file buffer.
// AKA 500Hz.
#define TASKS_PER_FRAME 20
// A task can be executed every 100us, AKA 10kHz.
#define TASK_INTERVAL_US (FRAME_TIME_US / TASKS_PER_FRAME)
// Frame buffers store data for the main loop to write to files. Increasing this
// number allows the main loop to get caught up longer waiting for other things
// to finish before attending to waiting data without losing data.
#define NUM_FRAME_BUFFERS 256
// Writing this many bytes to the SD card at a time results in improved 
// performance.
#define SD_SECTOR_SIZE 512
#define FILE_BUFFER_SIZE (SD_SECTOR_SIZE * 16)
// Transmitting this many bytes at a time over the serial connection is the most
// optimal rate possible.
#define USB_PACKET_SIZE 64

// This lights up when there is an error.
#define PIN_ONBOARD_LED 13

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

// Pauses execution of the program for a single clock cycle
#define DELAY_CLOCK_CYCLE __asm__("nop\n")
// Pauses execution of the program for 3 clock cycles. Our clock runs at 600MHz,
// so this results in a 5ns delay.
#define DELAY_5NS                                                              \
  DELAY_CLOCK_CYCLE;                                                           \
  DELAY_CLOCK_CYCLE;                                                           \
  DELAY_CLOCK_CYCLE
#define DELAY_10NS                                                             \
  DELAY_5NS;                                                                   \
  DELAY_5NS
#define DELAY_15NS                                                             \
  DELAY_5NS;                                                                   \
  DELAY_5NS;                                                                   \
  DELAY_5NS
#define DELAY_20NS                                                             \
  DELAY_5NS;                                                                   \
  DELAY_5NS;                                                                   \
  DELAY_5NS;                                                                   \
  DELAY_5NS
#define DELAY_25NS                                                             \
  DELAY_5NS;                                                                   \
  DELAY_5NS;                                                                   \
  DELAY_5NS;                                                                   \
  DELAY_5NS;                                                                   \
  DELAY_5NS

// When this is defined, ring buffers will trigger a critical error if they
// overflow.
#define DO_OVERFLOW_CHECKS

/**
 * Causes the program to stop running, the onboard LED to flash, and the provided error message to
 * repeatedly be printed to any serial monitor which is listening over the USB port.
 */
void criticalError(const char *error);
/**
 * Turns on or off the onboard LED, useful for debugging when the serial console is occupied.
 */
void setOnboardLed(const bool shouldBeOn);

template<int SIZE, typename T>
class RingBuffer {
private:
  T data[SIZE];
  uint32_t readIndex = 0, writeIndex = 0;
  void appendContinuous(const T *data, uint32_t len);
public:
  /**
   * Appends additional data to this ring buffer. Len must be smaller than SIZE.
   * Nothing has to be aligned.
   */
  void append(const T *data, uint32_t len);
  /**
   * Reads [len] unread bytes of data. Len must be smaller than or equal to SIZE
   * and unreadLen(). Data cannot be read such that it would cross over the
   * boundary of the buffer. For example, consider a RingBuffer<3>. It is valid
   * to do read(2) followed by read(1), but not valid to do read(2) followed by
   * read(2).
   */
  T *read(uint32_t len);
  /**
   * Moves the read pointer so that unreadLen() becomes zero.
   */
  void markAllDataAsRead();
  /** 
   * Returns how many bytes have been appended that have not yet been read.
   */
  uint32_t unreadLen();
};

#endif // UTIL_H_