#include "util.h"

void criticalError(const char *error) {
  Serial.begin(9600);
  pinMode(PIN_ONBOARD_LED, OUTPUT);
  while (true) {
    digitalWrite(PIN_ONBOARD_LED, HIGH);
    delay(200);
    digitalWrite(PIN_ONBOARD_LED, LOW);
    delay(200);
    if (Serial) Serial.println(error);
  }
}

void setOnboardLed(const bool shouldBeOn) {
  digitalWrite(PIN_ONBOARD_LED, shouldBeOn ? HIGH : LOW);
}

template<int SIZE, typename T>
void RingBuffer<SIZE, T>::appendContinuous(const T *data, uint32_t len) {
  T *writeTo = &this->data[this->writeIndex];
  this->writeIndex = (this->writeIndex + len) % SIZE;
  memcpy(writeTo, data, len * sizeof(T));
}

template<int SIZE, typename T>
void RingBuffer<SIZE, T>::append(const T *data, uint32_t len) {
  #ifdef DO_OVERFLOW_CHECKS
  if (this->unreadLen() + len >= SIZE) {
    criticalError("Ring buffer overflowed.");
  }
  #endif
  if (len + this->writeIndex > SIZE) {
    uint32_t partialSegmentLen = SIZE - this->writeIndex;
    this->appendContinuous(data, partialSegmentLen);
    this->appendContinuous(
      data + partialSegmentLen * sizeof(T), 
      len - partialSegmentLen
    );
  } else {
    this->appendContinuous(data, len);
  }
}

template<int SIZE, typename T>
T *RingBuffer<SIZE, T>::read(uint32_t len) {
  #ifdef DO_ALIGNMENT_CHECKS
  if (this->readIndex + len > SIZE) {
    criticalError("Ring buffer read with incorrect alignment.");
  }
  #endif
  T *retVal = &this->data[readIndex];
  this->readIndex = (this->readIndex + len) % SIZE;
  return retVal;
}

template<int SIZE, typename T>
void RingBuffer<SIZE, T>::markAllDataAsRead() {
  this->readIndex = this->writeIndex;
}

template<int SIZE, typename T>
uint32_t RingBuffer<SIZE, T>::unreadLen() {
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
