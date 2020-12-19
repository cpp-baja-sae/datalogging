#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <SdFat.h>

#include "util.h"

// This file and file_io.ino are responsible for reading data from and writing
// data to files. It is not responsible for taking raw data and formatting it
// in multiple resolutions, that would be the responsibility of formatting.h and
// formatting.ino. It contains a function to stream files over USB. It is
// recommended to disable other interrupts while this function is running to
// maximize speed.

struct DataFrame;
extern bool storedDatalogs[0x100];

/**
 * This function must be called before any other file IO tasks are performed.
 */
void setupSdCard();

/**
 * This function writes the contents of data_format.json (provided in 
 * DEFAULT_FORMAT_CONTENT from generated_format_info.h) to the provided file.
 * Returns false if the slot is poisoned and you need to reserve a different
 * slot.
 */
bool saveDataFormat(int slot, int file);

/**
 * This function removes all files contained in a slot.
 */
void deleteSlot(int slot);

/**
 * Returns the index of a slot which can be written to without overwriting
 * existing data. The same index will also not be returned on later calls to
 * this function. Returns -1 if no slot is available.
 */
int reserveSlot();

/**
 * Sends the contents of the provided file back to the host over the USB 
 * connection. Make sure to disable the task interrupt before using this for
 * max speed.
 */
void sendFileOverUsb(int slot, int file);

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
  uint32_t numWritesSinceLastFlush, flushThreshold;
  ExFile writeTo;
  // Set to true to throw away appended data. This should be true if a file
  // hasn't been opened yet.
  bool discardData;
public:
  /**
   * Creates a file buffer which does not write any of the data it receives.
   */
  FileBuffer();
  /**
   * Creates a file buffer which will write data to the specified file in the 
   * specified datalog slot.
   */
  FileBuffer(int slot, int file);
  /**
   * If this is true, you need to reserve a different slot.
   */
  bool isPoisoned();
  /**
   * Appends additional data to the buffer.
   */
  void append(const DataFrame &frame);
  /**
   * Sets the threshold where flushIfNeeded() will perform a flush. The value is
   * how many bytes have to be written to the file for this to happen. It will
   * be rounded down to the nearest multiple of SD_SECTOR_SIZE.
   */
  void setFlushThreshold(int bytes) {
    this->flushThreshold = bytes / SD_SECTOR_SIZE;
    if (this->flushThreshold < 1) this->flushThreshold = 1;
  }
  /**
   * Writes a sector of data to the file (if enough data is available to do so.)
   * Returns true if there is enough data to write another sector of data after
   * this function returns.
   */
  bool writeSector();
  /**
   * Ensures that written data has been saved to the card. Returns true if a 
   * flush was performed.
   */
  bool flushIfNeeded();
  /**
   * Closes the file this buffer is writing to.
   */
  void close();
};

#endif // FILE_IO_H_