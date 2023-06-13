#include "RHI/Vulkan/TextureView.h"

#include <RHI/Vulkan/Texture.h>

namespace RHI::Vulkan {
    struct VKTexturePrivate {
        std::shared_ptr<VKTexture> vkTexture;
        explicit VKTexturePrivate(std::shared_ptr<VKTexture> texture, const TextureViewCreateInfo& createInfo)
            : vkTexture(std::move(texture))
        {}
        VKTexturePrivate() = default;
    };

    VKTextureView::VKTextureView(std::shared_ptr<VKTexture> texture, const TextureViewCreateInfo& createInfo)
        : m_private(std::make_unique<VKTexturePrivate>(std::move(texture), createInfo))
    {}

    VKTextureView::~VKTextureView() = default;
} // namespace RHI::Vulkan
