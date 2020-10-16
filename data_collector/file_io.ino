#include <SPI.h>
#include <SdFat.h>
#include <stdlib.h>

#include "file_io.h"
#include "util.h"

SdExFat globalSd;
// This array stores true in an element if there is a datalog stored at that
// index (I.E. if the SD card has a folder named after the index.)
bool storedDatalogs[0x100];

/**
 * Buffer must point to a region of at least 7 bytes of memory. This function
 * places a null-terminated string in the form "slotIndex/fileIndex" into the
 * provided buffer.
 */
void makeFilePath(char *buffer, int slotIndex, int fileIndex) {
  itoa(slotIndex, buffer, 10);
  int firstPartLen = strlen(buffer);
  buffer[firstPartLen] = '/';
  // Put the second integer after the slash
  itoa(fileIndex, buffer + firstPartLen + 1, 10);
}

void setupSdCard() {
  if (!globalSd.begin(SdioConfig(FIFO_SDIO))) {
    criticalError("Failed to set up SD card.");
  }

  ExFile root = globalSd.open("/");
  if (!root) {
    criticalError("Failed to open root directory of SD card.");
  }

  // Read the list of files on the SD card so that we don't overwrite any
  // existing datalogs.
  for(int i = 0; i < 0x100; i++) {
    storedDatalogs[i] = false;
  }
  while (true) {
    ExFile entry = root.openNextFile();
    if (!entry) break;
    int parsedName = atoi(entry.name());
    storedDatalogs[parsedName] = true;
  }
}

