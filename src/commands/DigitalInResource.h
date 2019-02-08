#pragma once

#include <SimplePacketComs.h>
#include <cstdint>
#include <Arduino.h>

class DigitalInResource : public PacketEventAbstract {
  public:
  // Packet ID needs to be set
  DigitalInResource(int id, std::uint8_t ipin) : PacketEventAbstract(id), pin(ipin) {
    pinMode(pin, INPUT);
  }

  virtual ~DigitalInResource() {
  }

  // User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float *buffer);

  protected:
  std::uint8_t pin;
};
