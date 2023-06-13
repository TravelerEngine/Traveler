#pragma once

#include <memory>

namespace RHI {
    struct SwapChainCreateInfo;
    struct TextureViewCreateInfo;
    class TextureView;
    struct TextureCreateInfo {
    };
    class Texture {
    public:
        virtual ~Texture() = default;
        virtual std::shared_ptr<TextureView> CreateTextureView(const TextureViewCreateInfo& createInfo) = 0;
    };
} // namespace RHI
