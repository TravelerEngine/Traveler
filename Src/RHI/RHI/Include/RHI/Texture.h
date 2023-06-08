#pragma once

namespace RHI {
    struct SwapChainCreateInfo;
    struct TextureViewCreateInfo;
    class TextureView;

    struct TextureCreateInfo {
    };
    class Texture {
    public:
        virtual ~Texture() = default;
        virtual TextureView* CreateTextureView(const TextureViewCreateInfo& createInfo) = 0;
    };
} // namespace RHI
