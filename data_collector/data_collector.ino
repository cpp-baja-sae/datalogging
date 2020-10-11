#include "test.h"

// The USB protocol can transfer up to 64 bytes in a single packet.
const char *DATA_PACKET = "000000000000000000000000000000000000000000000000000000000000000\n";

void setup() {
}

int value = 0;
void loop() {
  Serial.print(DATA_PACKET);
}
