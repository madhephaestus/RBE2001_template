#include "DiscoveryPacket.h"
#include "AnalogInResource.h"
#include "AnalogOutResource.h"
#include "DigitalInResource.h"
#include "DigitalOutResource.h"
#include "EncoderResource.h"
#include "TestPacket.h"
#include <Arduino.h>

#define DISCOVERY_OP 1
#define IS_RESOURCE_IN_RANGE_OP 2

// User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void DiscoveryPacket::event(float *buffer) {
  std::int8_t *buf = (std::int8_t *)buffer;

  Serial.println("Got DiscoveryPacket event:");
  // Print the bytes we got
  for (int i = 0; i < 60; i++) {
    Serial.print(buf[i]);
    Serial.print(", ");
  }
  Serial.println();

  bool success = parsePacket(buf);

  // Clear the buffer
  for (int i = 0; i < 60; i++) {
    buf[i] = 0;
  }

  // Write the reply
  if (success) {
    buf[0] = 1;
  } else {
    buf[0] = 2;
  }
}

bool DiscoveryPacket::parsePacket(std::int8_t *buffer) {
  std::int8_t op = buffer[0];

  switch (op) {
  case DISCOVERY_OP:
    return parseDiscoveryPacket(buffer);

  case IS_RESOURCE_IN_RANGE_OP:
    return parseIsResourceInRange(buffer);

  default:
    return false;
  }
}

bool DiscoveryPacket::parseIsResourceInRange(std::int8_t *buffer) {
  int attachmentPointIndex = 2;
  std::uint8_t resourceType = buffer[1];
  std::uint8_t attachmentPoint = buffer[attachmentPointIndex];
  switch (resourceType) {
  case 1: {
    // DigitalIn
    switch (attachmentPoint) {
    case 1: {
      // Pin
      return true;
    }

    default:
      return false;
    }
  }

  case 2: {
    // DigitalOut
    switch (attachmentPoint) {
    case 1: {
      // Pin
      return true;
    }

    default:
      return false;
    }
  }

  case 3: {
    // AnalogIn
    switch (attachmentPoint) {
    case 1: {
      // Pin
      return true;
    }

    default:
      return false;
    }
  }

  case 4: {
    // AnalogOut
    switch (attachmentPoint) {
    case 1: {
// Pin
#if defined(ARDUINO_ARCH_ESP32)
      // Arduino doesn't support this yet, we will need to use
      // https://github.com/ERROPiX/ESP32_AnalogWrite
      return false;
#else
      return true;
#endif
    }

    default:
      return false;
    }
  }

  case 5: {
    // SerialConnection
    return false;
  }

  case 6: {
    // Servo
    switch (attachmentPoint) {
    case 1: {
      // Pin
      return true;
    }

    default:
      return false;
    }
  }

  case 7:
    // Stepper
    switch (attachmentPoint) {
    case 2: {
      // PinGroup
      std::int8_t count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2:
        return true;

      case 4:
        return true;

      default:
        return false;
      }
    }

    default:
      return false;
    }

  case 8: {
    // Encoder
    switch (attachmentPoint) {
    case 2: {
      // PinGroup
      std::int8_t count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2:
        return true;

      default:
        return false;
      }
    }

    default:
      return false;
    }
  }

  case 9: {
    // Button
    switch (attachmentPoint) {
    case 1:
      // Pin
      return true;

    default:
      return false;
    }
  }

  case 10: {
    // Ultrasonic
    switch (attachmentPoint) {
    case 2: {
      // PinGroup
      std::int8_t count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2:
        return true;

      default:
        return false;
      }
    }

    default:
      return false;
    }
  }

  case 11: {
    // PiezoelectricSpeaker
    switch (attachmentPoint) {
    case 1:
      // Pin
      return true;

    default:
      return false;
    }
  }

  default:
    Serial.println("invalid resource type");
    return false;
  }
}

bool DiscoveryPacket::parseDiscoveryPacket(std::int8_t *buffer) {
  int attachmentPointIndex = 3;
  std::int8_t packetId = buffer[1];
  std::uint8_t resourceType = buffer[2];
  std::uint8_t attachmentPoint = buffer[attachmentPointIndex];
  switch (resourceType) {
  case 1: {
    // DigitalIn
    switch (attachmentPoint) {
    case 1: {
      // Pin
      std::uint8_t pinNumber = buffer[attachmentPointIndex + 1];
      coms->attach(new DigitalInResource(packetId, pinNumber));
      return true;
    }

    default:
      return false;
    }
  }

  case 2: {
    // DigitalOut
    switch (attachmentPoint) {
    case 1: {
      // Pin
      std::uint8_t pinNumber = buffer[attachmentPointIndex + 1];
      coms->attach(new DigitalOutResource(packetId, pinNumber));
      return true;
    }

    default:
      return false;
    }
  }

  case 3: {
    // AnalogIn
    switch (attachmentPoint) {
    case 1: {
      // Pin
      std::uint8_t pinNumber = buffer[attachmentPointIndex + 1];
      coms->attach(new AnalogInResource(packetId, pinNumber));
      return true;
    }

    default:
      return false;
    }
  }

  case 4: {
    // AnalogOut
    switch (attachmentPoint) {
    case 1: {
      // Pin
      std::uint8_t pinNumber = buffer[attachmentPointIndex + 1];
      coms->attach(new AnalogInResource(packetId, pinNumber));
      return true;
    }

    default:
      return false;
    }
  }

  case 5: {
    // SerialConnection
    return false;
  }

  case 6: {
    // Servo
    switch (attachmentPoint) {
    case 1: {
      // Pin
      std::uint8_t pinNumber = buffer[attachmentPointIndex + 1];
      return true;
    }

    default:
      return false;
    }
  }

  case 7:
    // Stepper
    switch (attachmentPoint) {
    case 2: {
      // PinGroup
      std::int8_t count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2: {
        std::uint8_t pin1 = buffer[attachmentPointIndex + 2];
        std::uint8_t pin2 = buffer[attachmentPointIndex + 3];
        return true;
      }

      case 4: {
        std::uint8_t pin1 = buffer[attachmentPointIndex + 2];
        std::uint8_t pin2 = buffer[attachmentPointIndex + 3];
        std::uint8_t pin3 = buffer[attachmentPointIndex + 4];
        std::uint8_t pin4 = buffer[attachmentPointIndex + 5];
        return true;
      }

      default:
        return false;
      }
    }

    default:
      return false;
    }

  case 8: {
    // Encoder
    switch (attachmentPoint) {
    case 2: {
      // PinGroup
      std::int8_t count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2: {
        std::uint8_t pin1 = buffer[attachmentPointIndex + 2];
        std::uint8_t pin2 = buffer[attachmentPointIndex + 3];
        coms->attach(new EncoderResource(packetId, pin1, pin2));
        return true;
      }

      default:
        return false;
      }
    }

    default:
      return false;
    }
  }

  case 9: {
    // Button
    switch (attachmentPoint) {
    case 1: {
      // Pin
      std::uint8_t pinNumber = buffer[attachmentPointIndex + 1];
      return true;
    }

    default:
      return false;
    }
  }

  case 10: {
    // Ultrasonic
    switch (attachmentPoint) {
    case 2: {
      // PinGroup
      std::int8_t count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2: {
        std::uint8_t pin1 = buffer[attachmentPointIndex + 2];
        std::uint8_t pin2 = buffer[attachmentPointIndex + 3];
        return true;
      }

      default:
        return false;
      }
    }

    default:
      return false;
    }
  }

  case 11: {
    // PiezoelectricSpeaker
    switch (attachmentPoint) {
    case 1: {
      // Pin
      std::uint8_t pinNumber = buffer[attachmentPointIndex + 1];
      return true;
    }

    default:
      return false;
    }
  }

  default:
    Serial.println("invalid resource type");
    return false;
  }
}
