#include "TestPacket.h"
#include <Arduino.h>
#include <cstdint>

// User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void TestPacket::event(float *buffer) {
  byte *buf = (byte *)buffer;

  Serial.println("got test event");

  struct Regs {
    union {
      std::int16_t bc;

      struct {
        byte c;
        byte b;
      };
    };
  } regs;

  for (int i = 0; i < 60; i++) {
    Serial.print(buf[i]);
    Serial.print(", ");
  }
  Serial.println();

  regs.b = buf[3];
  regs.c = buf[4];
  Serial.println(regs.bc);

  buf[4] = 123;
}
