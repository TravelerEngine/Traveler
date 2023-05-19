#pragma once

#include <RHI/Instance.h>
#include <RHI/Vulkan/Api.h>
#include <vulkan/vulkan.hpp>

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

        uint32_t GetGpuCount() const override;
        std::shared_ptr<Gpu> GetGpu(uint32_t index) override;

        std::shared_ptr<vk::Instance> GetInstance() const;
    };
} // namespace RHI::Vulkan

extern "C" {
RHI_VULKAN_API RHI::Instance* RHIGetInstance();
}
