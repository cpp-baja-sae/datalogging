#ifndef UTIL_H_
#define UTIL_H_

#define FRAME_SIZE 100
#define TOTAL_NUM_LODS 8
#define NUM_LOW_RES_LODS (TOTAL_NUM_LODS - 1)
// A task can be executed every 100us, AKA 10kHz.
#define TASK_INTERVAL_US 100
// After 20 tasks have been performed, a frame should be saved to a file buffer.
// AKA 500Hz.
#define TASKS_PER_FRAME 20
#define FRAME_INTERVAL_US (TASK_INTERVAL_US * TASKS_PER_FRAME)
// Frame buffers store data for the main loop to write to files. Increasing this
// number allows the main loop to get caught up longer waiting for other things
// to finish before attending to waiting data without losing data.
#define NUM_FRAME_BUFFERS 256
// Writing this many bytes to the SD card at a time results in improved 
// performance.
#define SD_SECTOR_SIZE 512
#define FILE_BUFFER_SIZE (SD_SECTOR_SIZE * 16)

// When this is defined, ring buffers will trigger a critical error if they
// overflow.
#define DO_OVERFLOW_CHECKS

/**
 * Causes the program to stop running, the onboard LED to flash, and the provided error message to
 * repeatedly be printed to any serial monitor which is listening over the USB port.
 */
void criticalError(const char *error);

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
   * Returns how many bytes have been appended that have not yet been read.
   */
  uint32_t unreadLen();
};

#endif // UTIL_H_