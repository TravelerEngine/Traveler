#pragma once

#include "RHI/Surface.h"

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class VKDevice;
    class VKSurfacePrivate;

    // Platform function
    vk::SurfaceKHR CreateNativeSurface(const vk::Instance& instance, const SurfaceCreateInfo& createInfo);
    class VKSurface : public Surface {
        std::unique_ptr<VKSurfacePrivate> m_private;

    public:
        explicit VKSurface(std::shared_ptr<VKDevice> device, const SurfaceCreateInfo& info);
        ~VKSurface() override;

        vk::SurfaceKHR GetSurface() const;
        vk::SurfaceCapabilitiesKHR GetCapabilitiesKHR() const;
    };
} // namespace RHI::Vulkan
