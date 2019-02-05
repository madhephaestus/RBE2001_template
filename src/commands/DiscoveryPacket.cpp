#include "DiscoveryPacket.h"
#include "TestPacket.h"
#include <Arduino.h>

#define DISCOVERY_OP 1
#define IS_RESOURCE_IN_RANGE_OP 2
#define PROVISION_RESOURCE_OP 3

// User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void DiscoveryPacket::event(float *buffer) {
  byte *buf = (byte *)buffer;

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

bool DiscoveryPacket::parsePacket(byte *buffer) {
  byte op = buffer[0];

  switch (op) {
  case DISCOVERY_OP:
    return parseDiscoveryPacket(buffer);

  case IS_RESOURCE_IN_RANGE_OP:
    return parseIsResourceInRange(buffer);

  case PROVISION_RESOURCE_OP:
    return parseProvisionResource(buffer);

  default:
    return false;
  }
}

bool DiscoveryPacket::parseIsResourceInRange(byte *buffer) {
  byte resourceType = buffer[1];
  byte attachmentPoint = buffer[2];
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
      byte count = buffer[attachmentPoint + 1];
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
      byte count = buffer[attachmentPoint + 1];
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
      byte count = buffer[attachmentPoint + 1];
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

bool DiscoveryPacket::parseProvisionResource(byte *buffer) {
  return false;
}

bool DiscoveryPacket::parseDiscoveryPacket(byte *buffer) {
  byte packetId = buffer[1];
  byte resourceType = buffer[2];
  byte attachmentPoint = buffer[3];
  switch (resourceType) {
  case 1: {
    // DigitalIn
    switch (attachmentPoint) {
    case 1: {
      // Pin
      byte pinNumber = buffer[attachmentPoint + 1];
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
      byte pinNumber = buffer[attachmentPoint + 1];
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
      byte pinNumber = buffer[attachmentPoint + 1];
      coms->attach(new TestPacket(pinNumber));
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
      byte pinNumber = buffer[attachmentPoint + 1];
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
      byte pinNumber = buffer[attachmentPoint + 1];
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
      byte count = buffer[attachmentPoint + 1];
      switch (count) {
      case 2: {
        byte pin1 = buffer[attachmentPoint + 2];
        byte pin2 = buffer[attachmentPoint + 3];
        return true;
      }

      case 4: {
        byte pin1 = buffer[attachmentPoint + 2];
        byte pin2 = buffer[attachmentPoint + 3];
        byte pin3 = buffer[attachmentPoint + 4];
        byte pin4 = buffer[attachmentPoint + 5];
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
      byte count = buffer[attachmentPoint + 1];
      switch (count) {
      case 2: {
        byte pin1 = buffer[attachmentPoint + 2];
        byte pin2 = buffer[attachmentPoint + 3];
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
      byte pinNumber = buffer[attachmentPoint + 1];
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
      byte count = buffer[attachmentPoint + 1];
      switch (count) {
      case 2: {
        byte pin1 = buffer[attachmentPoint + 2];
        byte pin2 = buffer[attachmentPoint + 3];
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
      byte pinNumber = buffer[attachmentPoint + 1];
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
