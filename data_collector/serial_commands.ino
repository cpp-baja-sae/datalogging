#include "file_io.h"
#include "formatting.h"
#include "generated_format_info.h"
#include "serial_commands.h"
#include "util.h"

void handleWaitingCommands() {
  // We have received a command over USB...
  if (Serial.available()) {
    uint8_t command[2];
    for (int i = 0; i < 2; i++) {
      while (!Serial.available());
      command[i] = Serial.read();
    }
    pauseTaskTimer();
    while (!Serial);
    if ((command[0] & 0xF0) == 0x00) {
      // Read file.
      int slotIndex = command[1];
      int fileIndex = command[0] & 0x0F;
      sendFileOverUsb(slotIndex, fileIndex);
    } else if (command[0] == 0x10 && command[1] == 0x00) {
      // Get default data format (which will also be the format sent in realtime.)
      // This will never be bigger than a 32 bit value. If it is we have bigger
      // problems on our hand, pun intended.
      uint32_t size = DEFAULT_FORMAT_SIZE;
      Serial.write((char*) &size, 4);
      Serial.flush();
      Serial.send_now();
      Serial.write(DEFAULT_FORMAT_CONTENT, DEFAULT_FORMAT_SIZE);
      Serial.flush();
      Serial.send_now();
    } else if (command[0] == 0x10 && command[1] == 0x01) {
      // Report datalog slot usage.
      for (int i = 0; i < 0x100; i++) {
        if (currentDatalog == i) {
          Serial.write(0x02); // Slot is busy.
        } else if (storedDatalogs[i]) {
          Serial.write(0x01); // Slot contains data.
        } else {
          Serial.write(0x00); // Slot is empty.
        }
      }
      Serial.flush();
      Serial.send_now();
    } else if (command[0] == 0x10 && command[1] == 0x02) {
      // Start recording to a new slot.
      beginNewDatalog();
      // Confirm success.
      Serial.write(0xDD);
      Serial.flush();
      Serial.send_now();
    } else if (command[0] == 0x10 && command[1] == 0x03) {
      // Stop recording.
      endCurrentDatalog();
      // Confirm success.
      Serial.write(0xDD);
      Serial.flush();
      Serial.send_now();
    } else if (command[0] == 0x20) {
      // Delete all data in slot specified by command[1].
      deleteSlot(command[1]);
      // Confirm success.
      Serial.write(0xDD);
      Serial.flush();
      Serial.send_now();
    }
    resumeTaskTimer();
  }
}
