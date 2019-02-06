#include "DigitalInResource.h"
#include <Arduino.h>

// User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void DigitalInResource::event(float *buffer) {
  std::int8_t *buf = (std::int8_t *)buffer;

  // Clear the buffer
  for (int i = 0; i < 60; i++) {
    buf[i] = 0;
  }

  buf[0] = digitalRead(pin);
}

void DigitalInResource::provision(std::uint8_t pin) {
  pinMode(pin, INPUT);
}
