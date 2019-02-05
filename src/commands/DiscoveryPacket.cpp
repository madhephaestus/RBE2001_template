#include "DiscoveryPacket.h"
#include "TestPacket.h"
#include <Arduino.h>

// User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void DiscoveryPacket::event(float * buffer) {
    byte* buf = (byte*)buffer;

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
    // 12 is discovery type
    if (buffer[0] != 12) {
        Serial.println("invalid packet type");
        return false;
    }

    byte packetId = buffer[1];
    byte resourceType = buffer[2];
    byte attachmentPoint = buffer[3];
    if (resourceType == 1) {
        coms->attach(new TestPacket((int) packetId));
        return true;
    } else {
        Serial.println("invalid resource type");
    }

    return false;
}
