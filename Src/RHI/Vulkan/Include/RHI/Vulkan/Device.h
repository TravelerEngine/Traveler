#pragma once

#include "RHI/Device.h"

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class VKGpu;
    class VKDevicePrivate;
    class VKDevice : public Device
        , public std::enable_shared_from_this<VKDevice> {
        std::unique_ptr<VKDevicePrivate> m_private;

        explicit VKDevice(std::shared_ptr<VKGpu> GPU);

    public:
        [[nodiscard]] static std::shared_ptr<VKDevice> Create(std::shared_ptr<VKGpu> GPU)
        {
            return std::shared_ptr<VKDevice>(new VKDevice(std::move(GPU)));
        }
        ~VKDevice() override;

        std::shared_ptr<Surface> CreateSurface(SurfaceCreateInfo& info) override;

        uint32_t GetQueueCount() const override;
        std::shared_ptr<Queue> GetQueue(uint32_t index) override;

        std::shared_ptr<SwapChain> CreateSwapChain(SwapChainCreateInfo& info) override;

        vk::Device GetDevice() const;
        std::shared_ptr<VKGpu> GetGPU() const;
    };
} // namespace RHI::Vulkan
