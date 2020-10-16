#ifndef FILE_IO_H_
#define FILE_IO_H_

#include "util.h"

/**
 * This function must be called before any other file IO tasks are performed.
 */
void setupSdCard();

class FileBuffer {
private:
  RingBuffer<FILE_BUFFER_SIZE> data;

};

#endif // FILE_IO_H_