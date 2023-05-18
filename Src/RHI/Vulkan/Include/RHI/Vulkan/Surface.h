#pragma once

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class VKDevice;
    class VKSurfacePrivate;
    class VKSurface {
        std::shared_ptr<VKSurfacePrivate> m_private;

        explicit VKSurface(std::shared_ptr<VKDevice> device);

    public:
        [[nodiscard]] static std::shared_ptr<VKSurface> Create(std::shared_ptr<VKDevice> device)
        {
            return std::shared_ptr<VKSurface>(new VKSurface(std::move(device)));
        }
        ~VKSurface();
    };
} // namespace RHI::Vulkan
