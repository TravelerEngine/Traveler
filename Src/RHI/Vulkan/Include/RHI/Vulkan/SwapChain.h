#pragma once

#include <RHI/SwapChain.h>

#include <memory>

namespace RHI::Vulkan {
    class VKSwapChainPrivate;
    class VKDevice;
    class VKSwapChain : public SwapChain {
        std::unique_ptr<VKSwapChainPrivate> m_private;

    public:
        explicit VKSwapChain(std::shared_ptr<VKDevice> device, const SwapChainCreateInfo& info);
        ~VKSwapChain() override;
    };
} // namespace RHI::Vulkan
