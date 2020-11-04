#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <SdFat.h>

#include "util.h"

/**
 * This function must be called before any other file IO tasks are performed.
 */
void setupSdCard();

/**
 * This is a buffer which stores data to be written to a file. It gives flexible
 * control over when exactly the data is written. append() adds data to an 
 * internal buffer. writeSector() sends a chunk of data to the SD card, it
 * should be called once for every 512 bytes of data written (SD_SECTOR_SIZE.)
 * flushIfNeeded() will make sure data has been written to the file in the card,
 * it may take some time. You can call it as often as you want, it will
 * do nothing if you have not written enough data since last calling it.
 */
class FileBuffer {
private:
  RingBuffer<FILE_BUFFER_SIZE, char> data;
  uint32_t numWritesSinceLastFlush;
  ExFile writeTo;
public:
  /**
   * Creates a file buffer which will write data to the specified file in the 
   * specified datalog slot.
   */
  FileBuffer(int slot, int file);
  /**
   * Appends additional data to the buffer. len must be smaller than SIZE.
   */
  void append(const char *data, uint32_t len);
  /**
   * Writes a sector of data to the file (if enough data is available to do so.)
   * Returns true if there is enough data to write another sector of data after
   * this function returns.
   */
  bool writeSector();
  /**
   * Ensures that written data has been saved to the card.
   */
  void flushIfNeeded();
  /**
   * Closes the file this buffer is writing to.
   */
  void close();
};

#endif // FILE_IO_H_