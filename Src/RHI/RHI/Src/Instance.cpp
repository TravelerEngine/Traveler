#include "Common/DynamicLibrary.h"

#include <RHI/Instance.h>

#include <string>
#include <unordered_map>

static const std::unordered_map<std::string, RHI::RHIType> RHITypeMap{
    {"RHI-Vulkan", RHI::RHIType::Vulkan},
};

namespace RHI {
Instance *Instance::CreateByType(const std::string &type)
{
  const std::string RHI = "RHI-" + type;
  auto *dynamicLibrary = Common::DynamicLibraryManager::Singleton().Load(RHI);

  if (dynamicLibrary == nullptr) {
    return nullptr;
  }

  RHIGetInstanceFunc symbol =
      reinterpret_cast<RHIGetInstanceFunc>(dynamicLibrary->GetSymbol("RHIGetInstance"));

  if (symbol == nullptr) {
    return nullptr;
  }
  return symbol();
}
}  // namespace RHI
