#pragma once

#include <RHI/Instance.h>
#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
class VKInstancePrivate;

class VKInstance : public Instance
{
  std::unique_ptr<VKInstancePrivate> m_private;

 public:
  VKInstance();
  ~VKInstance() override;

  RHIType GetRHIType() const override { return RHIType::Vulkan; }

  vk::Instance GetInstance() const;
};
}  // namespace RHI::Vulkan
