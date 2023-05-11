#pragma once

#include <cstdint>
#include <iostream>
#include <type_traits>

namespace RHI {
using EnumType = uint32_t;

enum class RHIType : EnumType {
  Vulkan,
};

constexpr std::string_view ToString(RHIType value) {
  switch (value) {
  case RHIType::Vulkan:
    return "Vulkan";
  default:
    return "Unknown";
  }
}
} // namespace RHI
