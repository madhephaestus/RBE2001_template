#pragma once

#include <Esp32SimplePacketComs.h>
#include <SimplePacketComs.h>

class DiscoveryPacket : public PacketEventAbstract {
  public:
  DiscoveryPacket(UDPSimplePacket *icoms) : PacketEventAbstract(1), coms(icoms) {
  }

  virtual ~DiscoveryPacket() {
  }

  // User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float *buffer);

  protected:
  bool parsePacket(std::int8_t *buffer);
  bool parseIsResourceInRange(std::int8_t *buffer);
  bool parseProvisionResource(std::int8_t *buffer);
  bool parseDiscoveryPacket(std::int8_t *buffer);

  UDPSimplePacket *coms;
};
