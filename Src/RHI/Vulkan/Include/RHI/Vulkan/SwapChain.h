#pragma once

#include <RHI/SwapChain.h>

#include <memory>

namespace RHI::Vulkan {
    class VKSwapChainPrivate;
    class VKDevice;
    class VKSwapChain : public SwapChain {
        std::unique_ptr<VKSwapChainPrivate> m_private;

        explicit VKSwapChain(std::shared_ptr<VKDevice> device, SwapChainCreateInfo& info);

    public:
        [[nodiscard]] static std::shared_ptr<VKSwapChain> Create(std::shared_ptr<VKDevice> device, SwapChainCreateInfo& info)
        {
            return std::shared_ptr<VKSwapChain>(new VKSwapChain(std::move(device), info));
        }
        ~VKSwapChain() override;
    };
} // namespace RHI::Vulkan
