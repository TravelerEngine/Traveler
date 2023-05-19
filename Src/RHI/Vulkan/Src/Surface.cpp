#include "RHI/Vulkan/Surface.h"
#include "RHI/Vulkan/Device.h"
#include "RHI/Vulkan/Gpu.h"
#include "RHI/Vulkan/Instance.h"

namespace RHI::Vulkan {
    class VKSurfacePrivate {
    public:
        std::shared_ptr<VKDevice> vkDevice;
        vk::SurfaceKHR vkSurface;
        vk::SurfaceCapabilitiesKHR capabilities;

        explicit VKSurfacePrivate(std::shared_ptr<VKDevice> device, const SurfaceCreateInfo& info)
            : vkDevice(std::move(device))
        {
            auto instance = vkDevice->GetGPU()->GetInstance().GetInstance();
            vkSurface = CreateNativeSurface(*instance, info);
            capabilities = vkDevice->GetGPU()->GetVkPhysicalDevice().getSurfaceCapabilitiesKHR(vkSurface);
        }

        ~VKSurfacePrivate()
        {
            if (vkSurface) {
                vkDevice->GetGPU()->GetInstance().GetInstance()->destroySurfaceKHR(vkSurface);
            }
        }
    };

    VKSurface::VKSurface(std::shared_ptr<VKDevice> device, const SurfaceCreateInfo& info)
        : m_private(std::make_unique<VKSurfacePrivate>(std::move(device), info))
    {}

    VKSurface::~VKSurface() = default;

    vk::SurfaceKHR VKSurface::GetSurface() const
    {
        return m_private->vkSurface;
    }

    vk::SurfaceCapabilitiesKHR VKSurface::GetCapabilitiesKHR() const
    {
        return m_private->capabilities;
    }

} // namespace RHI::Vulkan
