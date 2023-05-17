#pragma once

#include "RHI/Gpu.h"

#include <memory>
#include <vulkan/vulkan.hpp>

namespace RHI::Vulkan {
    class VKDevice;
    class VKInstance;
    class VKGpuPrivate;
    class VKGpu : public Gpu {
        std::unique_ptr<VKGpuPrivate> m_private;

    public:
        explicit VKGpu(VKInstance* instance, vk::PhysicalDevice device);
        ~VKGpu() override;

        std::shared_ptr<VKDevice> CreateDevice();

        std::string DeviceName() const;

        const vk::PhysicalDevice& GetVkPhysicalDevice() const;
    };
} // namespace RHI::Vulkan
