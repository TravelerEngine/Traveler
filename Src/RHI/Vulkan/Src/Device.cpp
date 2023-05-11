#include "RHI/Vulkan/Device.h"

#include <iostream>

namespace RHI::Vulkan {
    class VKDevicePrivate {
    public:
        vk::Device m_device;
        vk::PhysicalDevice* m_GPU;
        vk::PhysicalDeviceProperties m_GPUProperties;
        vk::PhysicalDeviceMemoryProperties m_memoryProperties;

        vk::Queue m_queue;
        std::vector<vk::QueueFamilyProperties> m_queueFamilyProperties;

        uint32_t m_graphicsQueueFamilyIndex;
        uint32_t m_graphicsFamilyCount;

        VKDevicePrivate()
        {
        }

        ~VKDevicePrivate()
        {
        }

        vk::Result GetDeviceExtensionProperties()
        {
            vk::Result result;

            std::cout << "Device Extensions" << std::endl;
            std::cout << "=================" << std::endl;

            return result;
        }
    };

    VKDevice::VKDevice(vk::PhysicalDevice* GPU)
        : m_private(std::make_unique<VKDevicePrivate>())
    {}
    VKDevice::~VKDevice() = default;
} // namespace RHI::Vulkan
