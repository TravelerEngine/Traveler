#include "RHI/Vulkan/Gpu.h"

#include "RHI/Vulkan/Common.h"
#include "RHI/Vulkan/Device.h"
#include "RHI/Vulkan/Instance.h"
#include "vulkan/vulkan_core.h"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace RHI::Vulkan {
    class VKGpuPrivate {
    public:
        VKInstance* vkInstance;
        vk::PhysicalDevice vkPhysicalDevice;

        explicit VKGpuPrivate(VKInstance* instance, vk::PhysicalDevice device)
            : vkInstance(instance)
            , vkPhysicalDevice(device)
        {
        }

        ~VKGpuPrivate() = default;
    };

    VKGpu::VKGpu(VKInstance* instance, vk::PhysicalDevice device)
        : m_private(std::make_unique<VKGpuPrivate>(instance, device))
    {
    }

    VKGpu::~VKGpu() = default;

    std::shared_ptr<Device> VKGpu::CreateDevice()
    {
        return Create<VKDevice>(shared_from_this());
    }

    const vk::PhysicalDevice& VKGpu::GetVkPhysicalDevice() const
    {
        return m_private->vkPhysicalDevice;
    }

    std::string VKGpu::DeviceName() const
    {
        auto props = m_private->vkPhysicalDevice.getProperties();
        return props.deviceName;
    }

    VKInstance& VKGpu::GetInstance() const
    {
        return *m_private->vkInstance;
    }
} // namespace RHI::Vulkan
