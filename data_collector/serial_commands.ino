#include "generated/config.h"
#include "serial_commands.h"
#include "util.h"

void handleWaitingCommands() {
  // We have received a command over USB...
  if (Serial.available()) {
    setOnboardLed(true);
    uint8_t command[2];
    for (int i = 0; i < 2; i++) {
      while (!Serial.available());
      command[i] = Serial.read();
    }
    uint8_t commandId = command[0] & 0xF0;
    if (commandId == 0x00) {
      // Read file.
      pauseTaskTimer();
      int slotIndex = command[1];
      int fileIndex = command[0] & 0x0F;
      sendFileOverUsb(slotIndex, fileIndex);
      resumeTaskTimer();
    } else if (commandId == 0x10) {
      // Get default data format (which will also be the format sent in realtime.)
      while (!Serial);
      // This will never be bigger than a 32 bit value. If it is we have bigger
      // problems on our hand, pun intended.
      uint32_t size = DEFAULT_FORMAT_SIZE;
      Serial.write((char*) &size, 4);
      Serial.flush();
      Serial.send_now();
      Serial.write(DEFAULT_FORMAT_CONTENT, DEFAULT_FORMAT_SIZE);
      Serial.flush();
      Serial.send_now();
    }
    setOnboardLed(false);
  }
}
