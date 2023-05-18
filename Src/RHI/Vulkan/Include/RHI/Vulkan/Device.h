#pragma once

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class VKGpu;
    class VKSurface;
    class VKDevicePrivate;
    class VKDevice : public std::enable_shared_from_this<VKDevice> {
        std::unique_ptr<VKDevicePrivate> m_private;

        explicit VKDevice(std::shared_ptr<VKGpu> GPU);

    public:
        [[nodiscard]] static std::shared_ptr<VKDevice> Create(std::shared_ptr<VKGpu> GPU)
        {
            return std::shared_ptr<VKDevice>(new VKDevice(std::move(GPU)));
        }
        ~VKDevice();

        vk::Device GetDevice() const;
        std::shared_ptr<VKSurface> CreateSurface();
    };
} // namespace RHI::Vulkan
