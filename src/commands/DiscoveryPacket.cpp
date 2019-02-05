#include "DiscoveryPacket.h"
#include "TestPacket.h"
#include <Arduino.h>

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

  bool success = parseAndAttachPacket(buf);

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

bool DiscoveryPacket::parseAndAttachPacket(byte *buffer) {
  if (buffer[typeIndex] != discoveryType) {
    Serial.println("invalid packet type");
    return false;
  }

  byte packetId = buffer[packetIdIndex];
  byte resourceType = buffer[resourceTypeIndex];
  byte attachmentPoint = buffer[attachmentPointIndex];
  switch (resourceType) {
  case 1: {
    // DigitalIn
    switch (attachmentPoint) {
    case 1: {
      // Pin
      byte pinNumber = buffer[attachmentPointIndex + 1];
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
      byte pinNumber = buffer[attachmentPointIndex + 1];
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
      byte pinNumber = buffer[attachmentPointIndex + 1];
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
      byte pinNumber = buffer[attachmentPointIndex + 1];
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
      byte pinNumber = buffer[attachmentPointIndex + 1];
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
      byte count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2: {
        byte pin1 = buffer[attachmentPointIndex + 2];
        byte pin2 = buffer[attachmentPointIndex + 3];
        return true;
      }

      case 3: {
        byte pin1 = buffer[attachmentPointIndex + 2];
        byte pin2 = buffer[attachmentPointIndex + 3];
        byte pin3 = buffer[attachmentPointIndex + 4];
        byte pin4 = buffer[attachmentPointIndex + 5];
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
      byte count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2: {
        byte pin1 = buffer[attachmentPointIndex + 2];
        byte pin2 = buffer[attachmentPointIndex + 3];
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
      byte pinNumber = buffer[attachmentPointIndex + 1];
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
      byte count = buffer[attachmentPointIndex + 1];
      switch (count) {
      case 2: {
        byte pin1 = buffer[attachmentPointIndex + 2];
        byte pin2 = buffer[attachmentPointIndex + 3];
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
      byte pinNumber = buffer[attachmentPointIndex + 1];
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
