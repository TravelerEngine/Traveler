#pragma once

#include "RHI/Gpu.h"
#include <memory>

#include <vulkan/vulkan.hpp>

namespace RHI::Vulkan {
    class VKGpuPrivate;
    class VKInstance;
    class VKGpu : public Gpu {
        std::unique_ptr<VKGpuPrivate> m_private;

    public:
        VKGpu(const std::shared_ptr<VKInstance>& instance, vk::PhysicalDevice device);
        ~VKGpu() override;

        const vk::PhysicalDevice& GetVkPhysicalDevice() const;
    };
} // namespace RHI::Vulkan
