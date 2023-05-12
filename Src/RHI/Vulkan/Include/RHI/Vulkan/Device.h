#pragma once

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class VKGpu;
    class VKDevicePrivate;
    class VKDevice {
        std::unique_ptr<VKDevicePrivate> m_private;

    public:
        explicit VKDevice(VKGpu* GPU);
        ~VKDevice();
    };
} // namespace RHI::Vulkan
