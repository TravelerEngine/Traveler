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

        VKDevice* CreateDevice();

        const vk::PhysicalDevice& GetVkPhysicalDevice() const;
    };
} // namespace RHI::Vulkan
