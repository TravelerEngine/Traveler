#include "RHI/Vulkan/Texture.h"

#include "RHI/Common.h"
#include "RHI/Vulkan/Device.h"
#include "RHI/Vulkan/SwapChain.h"

#include <memory>

namespace RHI::Vulkan {
    struct VKTexturePrivate {
        std::shared_ptr<VKDevice> vkDevice;
        vk::Image vkImage;
        PixelFormat swapChainImageFormat;
        Extent swapChainExtent;
        explicit VKTexturePrivate(std::shared_ptr<VKDevice> device, const SwapChainCreateInfo& info, const vk::Image& image)
            : vkDevice(std::move(device))
            , vkImage(image)
        {
            swapChainImageFormat = info.format;
            swapChainExtent = info.extent;
        }

        ~VKTexturePrivate() = default;
    };

    VKTexture::VKTexture(std::shared_ptr<VKDevice> device, const SwapChainCreateInfo& info, const vk::Image& image)
        : m_private(std::make_unique<VKTexturePrivate>(std::move(device), info, image))
    {}

    VKTexture::~VKTexture() = default;

    TextureView* VKTexture::CreateTextureView(const TextureViewCreateInfo& createInfo)
    {
        return nullptr;
    }
} // namespace RHI::Vulkan
