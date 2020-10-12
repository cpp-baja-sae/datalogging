#include <SPI.h>
#include <SD.h>
#include <stdlib.h>

#define FRAME_SIZE 100
#define TOTAL_NUM_LODS 8
#define NUM_LOW_RES_LODS (TOTAL_NUM_LODS - 1)
// A task can be executed every 100us, AKA 10kHz.
#define TASK_INTERVAL_US 100
// After 20 tasks have been performed, a frame should be saved to a file buffer.
// AKA 500Hz.
#define TASKS_PER_FRAME 20

void criticalError(const char *error) {
  Serial.begin(9600);
  while (!Serial);
  pinMode(13, OUTPUT);
  while (true) {
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    Serial.println(error);
  }
}

struct FileBuffer {

};

// Buffer must point to a region of at least 7 bytes of memory. This function
// places a null-terminated string in the form "slotIndex/fileIndex" into the
// provided buffer.
void makeFilePath(char *buffer, int slotIndex, int fileIndex) {
  itoa(slotIndex, buffer, 10);
  int firstPartLen = strlen(buffer);
  buffer[firstPartLen] = '/';
  // Put the second integer after the slash
  itoa(fileIndex, buffer + firstPartLen + 1, 10);
}

// This array stores true in an element if there is a datalog stored at that
// index (I.E. if the SD card has a folder named after the index.)
bool storedDatalogs[0x100];
void setup() {
  // The main serial connection is over USB and the Teensy bumps up the baud 
  // rate to the maximum USB speed automatically.
  Serial.begin(9600);
  while (!Serial);

  if (!SD.begin(BUILTIN_SDCARD)) {
    criticalError("Failed to load SD card.");
  }

  File root = SD.open("/");

  // Read the list of files on the SD card so that we don't overwrite any
  // existing datalogs.
  for(int i = 0; i < 0x100; i++) {
    storedDatalogs[i] = false;
  }
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    int parsedName = atoi(entry.name());
    storedDatalogs[parsedName] = true;
  }

  File test = SD.open("12/0", FILE_WRITE);
  if (!test) {
    criticalError("Failed to open file");
  }
  char buf[1024];
  while (true) {
    for (int i = 0; i < 1024; i++) {
      test.write(buf, 512);
      test.write(buf, 512);
      test.flush();
      Serial.write("\n");
    }
    test.close();
    test = SD.open("12/0", FILE_WRITE);
  }
  test.close();
}

void loop() {
}
