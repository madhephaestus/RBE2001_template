#include "AnalogInResource.h"

// User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void AnalogInResource::event(float *buffer) {
  std::int8_t *buf = (std::int8_t *)buffer;

  // Clear the buffer
  for (int i = 0; i < 60; i++) {
    buf[i] = 0;
  }

  int value = analogRead(pin);
  buf[0] = value & 0xF;
  buf[1] = value & 0xF0;
}
