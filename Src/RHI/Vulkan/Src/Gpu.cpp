#include "RHI/Vulkan/Gpu.h"

#include <RHI/Vulkan/Instance.h>

#include <utility>

#include <unordered_map>

namespace RHI::Vulkan {
    class VKGpuPrivate {
    public:
        std::shared_ptr<VKInstance> instance;
        vk::PhysicalDevice device;
        VKGpuPrivate(std::shared_ptr<VKInstance> instance, vk::PhysicalDevice device)
            : instance(std::move(instance))
            , device(device)
        {
        }
        ~VKGpuPrivate() = default;
    };

    VKGpu::VKGpu(const std::shared_ptr<VKInstance>& instance, vk::PhysicalDevice device)
        : m_private(std::make_unique<VKGpuPrivate>(instance, device))
    {
    }

    VKGpu::~VKGpu() = default;

    const vk::PhysicalDevice& VKGpu::GetVkPhysicalDevice() const
    {
        return m_private->device;
    }
} // namespace RHI::Vulkan
