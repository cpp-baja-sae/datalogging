#include "file_io.h"
#include "util.h"

void setup() {
  setupSdCard();

  FileBuffer test(23, 5);
  for (int i = 0; i < 100; i++) {
    test.append("Hello World!", 12);
  }
  while (test.writeSector());
  test.close();

  criticalError("Nothing else to do.");
}

void loop() {
}
