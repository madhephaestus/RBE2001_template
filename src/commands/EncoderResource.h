#pragma once

#include <SimplePacketComs.h>
#include <cstdint>
#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32)
#include <ESP32Encoder.h>
#else
#include <Encoder.h>
#endif

class EncoderResource : public PacketEventAbstract {
  public:
  // Packet ID needs to be set
  EncoderResource(int id, std::uint8_t ipin1, std::uint8_t ipin2)
    : PacketEventAbstract(id), pin1(ipin1), pin2(ipin2) {
#if defined(ARDUINO_ARCH_ESP32)
    enc.attachHalfQuad(pin1, pin2);
#else
    enc = Encoder(pin1, pin2);
#endif
  }

  virtual ~EncoderResource() {
  }

  // User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float *buffer);

  protected:
  std::uint8_t pin1;
  std::uint8_t pin2;

#if defined(ARDUINO_ARCH_ESP32)
  ESP32Encoder enc;
#else
  Encoder enc;
#endif
};
