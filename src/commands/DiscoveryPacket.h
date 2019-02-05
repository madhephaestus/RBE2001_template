#if !defined(DISCOVERYPACKET_H)
#define DISCOVERYPACKET_H
#include <Esp32SimplePacketComs.h>
#include <SimplePacketComs.h>
#include <cstdint>

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
  bool parseAndAttachPacket(byte *buffer);



  UDPSimplePacket *coms;

  int typeIndex{0};
  int packetIdIndex{1};
  int resourceTypeIndex{2};
  int attachmentPointIndex{3};

  int discoveryType{12};
};
#endif
