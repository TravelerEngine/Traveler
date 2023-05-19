#include "RHI/Vulkan/SwapChain.h"

#include <RHI/Vulkan/Device.h>
#include <RHI/Vulkan/Gpu.h>
#include <RHI/Vulkan/Surface.h>

namespace RHI::Vulkan {
    class VKSwapChainPrivate {
        std::shared_ptr<VKDevice> device;

    public:
        explicit VKSwapChainPrivate(std::shared_ptr<VKDevice> device, SwapChainCreateInfo& info)
            : device(std::move(device))
        {
            auto surface = info.surface;
            // device->GetGPU()->GetVkPhysicalDevice().getSurfaceCapabilitiesKHR();
        }
        ~VKSwapChainPrivate() = default;
    };

    VKSwapChain::VKSwapChain(std::shared_ptr<VKDevice> device, SwapChainCreateInfo& info)
        : m_private(std::make_unique<VKSwapChainPrivate>(std::move(device), info))
    {}
    VKSwapChain::~VKSwapChain() = default;
} // namespace RHI::Vulkan
