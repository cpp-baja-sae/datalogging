#include "test.h"

void setup() {
}

void loop() {
  int value = 0;
  for (int i = 0; i < 600 * 1000 * 1000; i++) {
    value += i;
    value -= i;
  }
}
