#pragma once

#include <RHI/Texture.h>
#include <memory>
#include <vulkan/vulkan.hpp>

namespace RHI::Vulkan {
    class VKDevice;
    class VKTexturePrivate;
    class VKTexture : public Texture {
        std::unique_ptr<VKTexturePrivate> m_private;

    public:
        explicit VKTexture(std::shared_ptr<VKDevice> device, const SwapChainCreateInfo& info, const vk::Image& image);
        TextureView* CreateTextureView(const TextureViewCreateInfo& createInfo) override;
        ~VKTexture() override;
    };
} // namespace RHI::Vulkan
