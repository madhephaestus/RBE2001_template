#pragma once

#include "../resource/Resource.h"
#include "DiscoveryMetadata.h"
#include "ResourceServer.h"
#include <Esp32SimplePacketComs.h>
#include <SimplePacketComs.h>
#include <array>
#include <memory>
#include <vector>

class DiscoveryPacket : public PacketEventAbstract {
  public:
  DiscoveryPacket(UDPSimplePacket *icoms) : PacketEventAbstract(DISCOVERY_PACKET_ID) {
    coms=icoms;
  }

  virtual ~DiscoveryPacket() {
  }

  // User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float *buffer);

  protected:
  /**
   * Parses a general discovery packet and writes the response.
   *
   * Section 2.1.1.
   *
   * @param buffer The packet payload.
   */
  void parseGeneralDiscoveryPacket(std::int8_t *buffer);

  /**
   * Parses a discovery packet and writes the response.
   *
   * Section 2.1.2.
   *
   * @param buffer The packet payload.
   * @param dest The reply buffer.
   */
  void parseDiscoveryPacket(const std::int8_t *buffer, std::int8_t *dest);

  /**
   * Parses a group discovery packet and writes the response.
   *
   * Section 2.1.3.
   *
   * @param buffer The packet payload.
   * @param dest The reply buffer.
   */
  void parseGroupDiscoveryPacket(const std::int8_t *buffer, std::int8_t *dest);

  /**
   * Parses a group member discovery packet and writes the response.
   *
   * Section 2.1.4.
   *
   * @param buffer The packet payload.
   * @param dest The reply buffer.
   */
  void parseGroupMemberDiscoveryPacket(const std::int8_t *buffer, std::int8_t *dest);

  /**
   * Parses a discard discovery packet and writes the response.
   *
   * Section 2.1.5.
   *
   * @param buffer The packet payload.
   * @param dest The reply buffer.
   */
  void parseDiscardDiscoveryPacket(const std::int8_t *buffer, std::int8_t *dest);

  /**
   * Attaches a resource.
   *
   * @param packetId The new packet ID.
   * @param resource The resource type.
   * @param attachment The attachment point type.
   * @param attachmentData Any attachment data.
   * @param dest The destination array to write the status and payload to.
   */
  virtual void attachResource(std::int8_t packetId,
                              std::int8_t resource,
                              std::int8_t attachment,
                              const std::int8_t *attachmentData,
                              std::int8_t *dest);

  UDPSimplePacket *coms;
  std::vector<ResourceServer *> resourceServers{};
};
