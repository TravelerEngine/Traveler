#include "RHI/Vulkan/SwapChain.h"

#include <RHI/Vulkan/Common.h>
#include <RHI/Vulkan/Device.h>
#include <RHI/Vulkan/Gpu.h>
#include <RHI/Vulkan/Queue.h>
#include <RHI/Vulkan/Surface.h>
#include <RHI/Vulkan/Texture.h>

#include <limits>
#include <memory>

namespace RHI::Vulkan {
    class VKSwapChainPrivate {
        std::shared_ptr<VKDevice> vkDevice;
        vk::SurfaceFormatKHR format;
        vk::PresentModeKHR presentMode;
        vk::SwapchainKHR vkSwapChainKHR;
        std::vector<std::shared_ptr<VKTexture>> swapChainImages;

    public:
        explicit VKSwapChainPrivate(std::shared_ptr<VKDevice> device, const SwapChainCreateInfo& info)
            : vkDevice(std::move(device))
        {
            auto vkPhysicalDevice = vkDevice->GetGPU()->GetVkPhysicalDevice();
            auto surface = std::dynamic_pointer_cast<VKSurface>(info.surface);
            format = chooseSwapSurfaceFormat(vkPhysicalDevice.getSurfaceFormatsKHR(surface->GetSurface()));
            presentMode = chooseSwapPresentMode(vkPhysicalDevice.getSurfacePresentModesKHR(surface->GetSurface()));

            vk::Extent2D extent {info.extent.width, info.extent.height};

            vk::SwapchainCreateInfoKHR createInfo;
            createInfo
                .setSurface(surface->GetSurface())
                .setMinImageCount(surface->GetCapabilitiesKHR().minImageCount + 1)
                .setImageFormat(format.format)
                .setImageColorSpace(vk::ColorSpaceKHR::eVkColorspaceSrgbNonlinear)
                .setPresentMode(presentMode)
                .setClipped(1u)
                .setPreTransform(surface->GetCapabilitiesKHR().currentTransform)
                .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
                .setImageSharingMode(vk::SharingMode::eExclusive)
                .setImageExtent(extent)
                .setImageArrayLayers(1)
                .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
                .setOldSwapchain(nullptr);
            assert(vkDevice->GetDevice().createSwapchainKHR(&createInfo, nullptr, &vkSwapChainKHR) == vk::Result::eSuccess);

            auto vkImages = vkDevice->GetDevice().getSwapchainImagesKHR(vkSwapChainKHR);
            swapChainImages.resize(vkImages.size());
            for (const auto& vkImage : vkImages) {
                swapChainImages.emplace_back(Create<VKTexture>(device, info, vkImage));
            }
        }

        ~VKSwapChainPrivate()
        {
            vkDevice->GetDevice().destroySwapchainKHR(vkSwapChainKHR);
        }

        static vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats)
        {
            for (auto const format : formats) {
                if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eVkColorspaceSrgbNonlinear) {
                    return format;
                }
            }

            return formats[0];
        }

        static vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& presentModes)
        {
            for (auto const mode : presentModes) {
                if (mode == vk::PresentModeKHR::eMailbox) {
                    return mode;
                }
            }
            return vk::PresentModeKHR::eFifo;
        }
    };

    VKSwapChain::VKSwapChain(std::shared_ptr<VKDevice> device, const SwapChainCreateInfo& info)
        : m_private(std::make_unique<VKSwapChainPrivate>(std::move(device), info))
    {}
    VKSwapChain::~VKSwapChain() = default;
} // namespace RHI::Vulkan
