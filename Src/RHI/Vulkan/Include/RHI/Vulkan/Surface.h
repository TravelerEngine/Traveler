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

        explicit VKSurface(std::shared_ptr<VKDevice> device, const SurfaceCreateInfo& info);

    public:
        [[nodiscard]] static std::shared_ptr<VKSurface> Create(std::shared_ptr<VKDevice> device, const SurfaceCreateInfo& info)
        {
            return std::shared_ptr<VKSurface>(new VKSurface(std::move(device), info));
        }
        ~VKSurface() override;

        vk::SurfaceKHR GetSurface() const;
        vk::SurfaceCapabilitiesKHR GetCapabilitiesKHR() const;
    };
} // namespace RHI::Vulkan
