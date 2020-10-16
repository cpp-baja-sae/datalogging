// #include <SD.h>
#include <SPI.h>
#include <SdFat.h>
#include <stdlib.h>

// This method can be used to test how fast we can write to the SD card. Every time an 'a' is
// sent over serial, 1MiB has been written to the SD card. Use serial_test.sh to measure how fast
// the 'a's are coming in and multiply it by 1MiB (1024B * 1024B)
//
// From a 5 minute test, a write speed of 15MiB/s can be fairly consistently maintained, reaching 
// 17MiB/s for extended periods of time. Occasionally dips down to 4MiB/s.
void testSdPerformance() {
  SdExFat sd;

  Serial.begin(9600);
  while (!Serial && millis() < 5000);

  if (!sd.begin(SdioConfig(FIFO_SDIO))) {
    criticalError("Failed to load SD card.");
  }

  sd.mkdir("12");
  ExFile test = sd.open("12/1", FILE_WRITE);
  if (!test) {
    criticalError("Failed to open file");
  }
  char buf[1024];
  while (true) {
    for (int i = 0; i < 1024; i++) {
      test.write(buf, 512);
      test.write(buf, 512);
    }
    test.flush();
    Serial.write('a');
  }
  test.close();
}