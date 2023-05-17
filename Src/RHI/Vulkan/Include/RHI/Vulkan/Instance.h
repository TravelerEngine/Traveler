#pragma once

#include <RHI/Instance.h>
#include <vulkan/vulkan.hpp>
#include <RHI/Vulkan/Api.h>

#include <memory>

#include "RHI/Vulkan/Common.h"

namespace RHI::Vulkan {
    class VKInstancePrivate;

    class VKInstance : public Instance {
        std::unique_ptr<VKInstancePrivate> m_private;

    public:
        VKInstance();
        ~VKInstance() override;

        RHIType GetRHIType() const override
        {
            return RHIType::Vulkan;
        }

        std::shared_ptr<vk::Instance> GetInstance();
        std::vector<LayerProperties> GetLayerProperties();
    };
} // namespace RHI::Vulkan

extern "C" {
    RHI_VULKAN_API RHI::Instance* RHIGetInstance();
}
