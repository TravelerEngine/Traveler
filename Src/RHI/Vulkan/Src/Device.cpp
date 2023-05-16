#include "RHI/Vulkan/Device.h"

#include "RHI/Vulkan/Gpu.h"

#include <iostream>

namespace RHI::Vulkan {
    const std::vector<const char*> extensions {};
    const std::vector<const char*> layers {"VK_LAYER_KHRONOS_validation"};

    class VKDevicePrivate {
    public:
        VKGpu* m_GPU;
        std::vector<vk::QueueFamilyProperties> m_queueFamilyProperties;
        uint32_t m_graphicsQueueFamilyIndex;

        explicit VKDevicePrivate(VKGpu* GPU)
            : m_GPU(GPU)
        {
            CreateDevice();
        }

        ~VKDevicePrivate() = default;

        vk::Result CreateDevice()
        {
            vk::Result result;

            auto physicalDevice {m_GPU->GetVkPhysicalDevice()};

            uint32_t queueFamilyCount;
            physicalDevice.getQueueFamilyProperties(&queueFamilyCount, nullptr);
            m_queueFamilyProperties.resize(queueFamilyCount);
            physicalDevice.getQueueFamilyProperties(&queueFamilyCount, m_queueFamilyProperties.data());

            std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
            for (unsigned int i = 0; i < queueFamilyCount; ++i) {
                if (m_queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                    std::vector<float> queuePriorities(m_queueFamilyProperties[i].queueCount, 1.0f);
                    vk::DeviceQueueCreateInfo info;

                    info.queueFamilyIndex = i;
                    info.queueCount = m_queueFamilyProperties[i].queueCount;
                    info.pQueuePriorities = queuePriorities.data();
                    queueCreateInfos.emplace_back(info);
                }
            }

            return result;
        }
    };

    VKDevice::VKDevice(VKGpu* GPU)
        : m_private(std::make_unique<VKDevicePrivate>(GPU))
    {}
    VKDevice::~VKDevice() = default;
} // namespace RHI::Vulkan
