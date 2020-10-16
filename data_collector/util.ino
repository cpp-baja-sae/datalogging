#include "util.h"

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

template<int SIZE>
void RingBuffer<SIZE>::appendContinuous(const char *data, uint32_t len) {
  char *writeTo = &this->data[this->writeIndex];
  this->writeIndex = (this->writeIndex + len) % SIZE;
  for (; len > 0; len--) {
    *writeTo = *data;
    data++;
    writeTo++;
  }
}

template<int SIZE>
void RingBuffer<SIZE>::append(const char *data, uint32_t len) {
  if (len + this->writeIndex > SIZE) {
    uint32_t partialSegmentLen = SIZE - this->writeIndex;
    this->appendContinuous(data, partialSegmentLen);
    this->appendContinuous(data + partialSegmentLen, len - partialSegmentLen);
  } else {
    this->appendContinuous(data, len);
  }
}

template<int SIZE>
char *RingBuffer<SIZE>::read(uint32_t len) {
  char *retVal = &this->data[readIndex];
  this->readIndex = (this->readIndex + len) % SIZE;
  return retVal;
}

template<int SIZE>
uint32_t RingBuffer<SIZE>::unreadLen() {
  if (this->writeIndex >= this->readIndex) {
    // The write pointer has not looped around the end of the buffer compared to 
    // the read pointer.
    return this->writeIndex - this->readIndex;
  } else {
    // The write pointer has looped around back to the start so the read pointer
    // is numerically larger.
    return SIZE - (this->readIndex - this->writeIndex);
  }
}
