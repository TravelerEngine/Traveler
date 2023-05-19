#pragma once

#include "RHI/Gpu.h"

#include <memory>
#include <vulkan/vulkan.hpp>

namespace RHI::Vulkan {
    class VKInstance;
    class VKGpuPrivate;
    class VKGpu : public Gpu
        , public std::enable_shared_from_this<VKGpu> {
        std::unique_ptr<VKGpuPrivate> m_private;

        explicit VKGpu(VKInstance* instance, vk::PhysicalDevice device);

    public:
        [[nodiscard]] static std::shared_ptr<VKGpu> Create(VKInstance* instance, vk::PhysicalDevice device)
        {
            return std::shared_ptr<VKGpu>(new VKGpu(instance, device));
        }
        ~VKGpu() override;

        std::shared_ptr<Device> CreateDevice() override;
        std::string DeviceName() const override;
        const vk::PhysicalDevice& GetVkPhysicalDevice() const;
    };
} // namespace RHI::Vulkan
