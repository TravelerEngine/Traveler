#pragma once

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class VKDevicePrivate;
    class VKDevice {
        std::unique_ptr<VKDevicePrivate> m_private;

    public:
        explicit VKDevice(vk::PhysicalDevice* GPU);
        ~VKDevice();
    };
} // namespace RHI::Vulkan
