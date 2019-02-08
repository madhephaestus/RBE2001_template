#include "AnalogOutResource.h"

// User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void AnalogOutResource::event(float *buffer) {
  std::int8_t *buf = (std::int8_t *)buffer;
  std::uint16_t value = buf[0] | buf[1] << 8;

  // Clear the buffer
  for (int i = 0; i < 60; i++) {
    buf[i] = 0;
  }

#if defined(ARDUINO_ARCH_ESP32)
#else
  analogWrite(pin, value);
#endif
}
