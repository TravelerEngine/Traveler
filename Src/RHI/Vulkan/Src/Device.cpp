#include "RHI/Vulkan/Device.h"

#include "RHI/Vulkan/Gpu.h"

#include <iostream>

namespace RHI::Vulkan {
    const std::vector<const char*> extensions {};
    const std::vector<const char*> layers {"VK_LAYER_KHRONOS_validation"};

    class VKDevicePrivate {
    public:
        VKGpu* m_GPU;
        vk::PhysicalDeviceProperties m_GPUProperties;
        vk::PhysicalDeviceMemoryProperties m_memoryProperties;

        std::vector<vk::QueueFamilyProperties> m_queueFamilyProperties;

        uint32_t m_graphicsQueueFamilyIndex;
        uint32_t m_graphicsFamilyCount;

        explicit VKDevicePrivate(VKGpu* GPU)
            : m_GPU(GPU)
        {
            CreateDevice();
        }

        ~VKDevicePrivate() = default;

        vk::Result CreateDevice()
        {
            vk::Result result;

            return result;
        }

        vk::Result GetDeviceExtensionProperties()
        {
            vk::Result result;

            std::cout << "Device Extensions" << std::endl;
            std::cout << "=================" << std::endl;

            return result;
        }
    };

    VKDevice::VKDevice(VKGpu* GPU)
        : m_private(std::make_unique<VKDevicePrivate>(GPU))
    {}
    VKDevice::~VKDevice() = default;
} // namespace RHI::Vulkan
