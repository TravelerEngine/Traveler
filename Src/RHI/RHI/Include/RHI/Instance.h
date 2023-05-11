#pragma once

#include "Common.h"

namespace RHI {
class Instance {
public:
  Instance(const Instance &) = delete;
  Instance &operator=(const Instance &) = delete;

  static Instance *CreateByType(const std::string &type);

  virtual RHIType GetRHIType() const = 0;

protected:
  explicit Instance() = default;
  virtual ~Instance() = default;
};

using RHIGetInstanceFunc = Instance *(*)();
} // namespace RHI
