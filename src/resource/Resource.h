#pragma once

#include "../commands/DiscoveryMetadata.h"
#include <array>
#include <cstdint>

class Resource {
  public:
  /**
   * This should connect the resource.
   *
   * @param resource The resource type.
   * @param attachment The attachment point type.
   * @param attachmentData Any attachment data.
   */
  Resource(std::int8_t resource, std::int8_t attachment, const std::int8_t *attachmentData) {
  }

  /**
   * This should disconnect the resource, if applicable.
   */
  virtual ~Resource() {
  }

  /**
   * Reads the payload and writes back to the buffer to send a response.
   *
   * @param buffer The buffer.
   */
  virtual void handlePayload(std::int8_t *buffer) = 0;
};
