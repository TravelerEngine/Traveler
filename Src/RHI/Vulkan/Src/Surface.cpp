#include "RHI/Vulkan/Surface.h"
#include "RHI/Vulkan/Device.h"
#include "RHI/Vulkan/Gpu.h"
#include "RHI/Vulkan/Instance.h"

namespace RHI::Vulkan {
    class VKSurfacePrivate {
    public:
        std::shared_ptr<VKDevice> device;
        vk::SurfaceKHR vkSurface;
        explicit VKSurfacePrivate(std::shared_ptr<VKDevice> device, const SurfaceCreateInfo& info)
            : device(std::move(device))
        {
            vkSurface = CreateNativeSurface(*device->GetGPU()->GetInstance().GetInstance(), info);
        }

        ~VKSurfacePrivate()
        {
            if (vkSurface) {
                device->GetGPU()->GetInstance().GetInstance()->destroySurfaceKHR(vkSurface);
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

} // namespace RHI::Vulkan
