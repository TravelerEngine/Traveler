#pragma once

#include <RHI/TextureView.h>

#include <memory>

namespace RHI::Vulkan {
    class VKTexture;
    class VKTexturePrivate;
    class VKTextureView : public TextureView {
        std::unique_ptr<VKTexturePrivate> m_private;

    public:
        explicit VKTextureView(std::shared_ptr<VKTexture> texture, const TextureViewCreateInfo& createInfo);
        ~VKTextureView() override;
    };
} // namespace RHI::Vulkan
