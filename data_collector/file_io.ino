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

ExFile clearAndOpenFileForWriting(int slotIndex, int fileIndex) {
  char fileName[7];
  itoa(slotIndex, fileName, 10);
  globalSd.mkdir(fileName);
  makeFilePath(fileName, slotIndex, fileIndex);
  // Delete any existing file data so that we're only writing new data.
  globalSd.remove(fileName);
  return globalSd.open(fileName, FILE_WRITE);
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

void saveDataFormat(int slot, int fileIndex) {
  ExFile file = clearAndOpenFileForWriting(slot, fileIndex);
  if (!file) {
    criticalError("Cannot save data format, failed to open file.");
  }
  file.write(DEFAULT_FORMAT_CONTENT, DEFAULT_FORMAT_SIZE);
  file.close();
}

void sendFileOverUsb(int slot, int fileIndex) {
  char fileName[7];
  makeFilePath(fileName, slot, fileIndex);
  ExFile file = globalSd.open(fileName, FILE_READ);
  if (!file) {
    uint64_t size = 0;
    Serial.write((char*) &size, 8);
    Serial.flush();
    Serial.send_now();
    criticalError("Cannot send file over USB, failed to open file.");
  }
  uint64_t size = file.size();
  uint64_t lastPacketSize = size % USB_PACKET_SIZE;
  while (!Serial);
  Serial.write((char*) &size, 8);
  Serial.flush();
  Serial.send_now();
  char buffer[USB_PACKET_SIZE];
  for (uint64_t p = 0; p < size / USB_PACKET_SIZE; p++) {
    file.read(&buffer[0], USB_PACKET_SIZE);
    Serial.write(&buffer[0], USB_PACKET_SIZE);
  }
  if (lastPacketSize > 0) {
    file.read(&buffer[0], lastPacketSize);
    Serial.write(&buffer[0], lastPacketSize);
  }
  file.close();
}

FileBuffer::FileBuffer() {
  this->discardData = true;
}

FileBuffer::FileBuffer(int slot, int file) {
  this->discardData = false;
  this->writeTo = clearAndOpenFileForWriting(slot, file);
  if (!this->writeTo) {
    criticalError("Failed to open file for file buffer.");
  }
  this->numWritesSinceLastFlush = 0;
}

void FileBuffer::append(const DataFrame &data) {
  if (this->discardData) {
    return;
  }
  auto dataPtr = reinterpret_cast<const char*>(&data);
  this->data.append(dataPtr, FRAME_SIZE);
}

bool FileBuffer::writeSector() {
  if (this->data.unreadLen() >= SD_SECTOR_SIZE) {
    this->writeTo.write(this->data.read(SD_SECTOR_SIZE), SD_SECTOR_SIZE);
    this->numWritesSinceLastFlush += 1;
  }
  return this->data.unreadLen() >= SD_SECTOR_SIZE;
}

bool FileBuffer::flushIfNeeded() {
  // Flush every 1MiB
  if (this->numWritesSinceLastFlush >= this->flushThreshold) {
    this->numWritesSinceLastFlush = 0;
    this->writeTo.flush();
    return true;
  } else {
    return false;
  }
}

void FileBuffer::close() {
  this->writeTo.close();
}

