#if !defined(TestPacket_H)
#define TestPacket_H
#include <SimplePacketComs.h>

class TestPacket: public PacketEventAbstract {
public:
	// Packet ID needs to be set
	TestPacket(int id) : PacketEventAbstract(id) {}

	virtual ~TestPacket() {}

	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};
#endif
