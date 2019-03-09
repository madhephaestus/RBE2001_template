#pragma once

#include "../commands/DiscoveryMetadata.h"
#include "Resource.h"
#include <Arduino.h>

class AnalogInResource : public Resource {
  public:
  AnalogInResource(std::int8_t resource, std::int8_t attachment, const std::int8_t *attachmentData)
    : Resource(resource, attachment, attachmentData), pin(attachmentData[0]) {
    pinMode(pin, INPUT);
  }

  virtual ~AnalogInResource() {
  }

  void handlePayload(std::int8_t *buffer) override {
    memset(buffer, 0, PAYLOAD_LENGTH * (sizeof buffer[0]));

    const int value = analogRead(pin);

    buffer[0] = value & 0xF;
    buffer[1] = value & 0xF0;
  }

  protected:
  std::int8_t pin;
};
