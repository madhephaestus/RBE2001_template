#pragma once

#include "../commands/DiscoveryMetadata.h"
#include "Resource.h"
#include <Arduino.h>

class DigitalOutResource : public Resource {
  public:
  DigitalOutResource(std::int8_t resource,
                     std::int8_t attachment,
                     const std::int8_t *attachmentData)
    : Resource(resource, attachment, attachmentData), pin(attachmentData[0]) {
    pinMode(pin, OUTPUT);
  }

  virtual ~DigitalOutResource() {
  }

  void handlePayload(std::int8_t *buffer) override {
    Serial.println("5");
    digitalWrite(pin, buffer[0]);

    memset(buffer, 0, PAYLOAD_LENGTH * (sizeof buffer[0]));
    Serial.println("6");
  }

  protected:
  std::int8_t pin;
};
