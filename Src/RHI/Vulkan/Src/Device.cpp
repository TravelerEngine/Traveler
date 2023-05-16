#include "RHI/Vulkan/Device.h"

#include "RHI/Vulkan/Gpu.h"
#include "vulkan/vulkan_structs.hpp"

#include <iostream>

namespace RHI::Vulkan {
    const std::vector<const char*> extensions
    {
#if PLATFORM_MACOS
        "VK_KHR_portability_subset"
#endif
    };
    const std::vector<const char*> layers {"VK_LAYER_KHRONOS_validation"};

    class VKDevicePrivate {
    public:
        VKGpu* m_GPU;
        uint32_t m_graphicsQueueFamilyIndex;
        std::vector<vk::QueueFamilyProperties> m_queueFamilyProperties;
        vk::Device vkDevice;

        explicit VKDevicePrivate(VKGpu* GPU)
            : m_GPU(GPU)
        {
            CreateDevice();
        }

        ~VKDevicePrivate()
        {
            vkDevice.destroy();
        }

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

            vk::DeviceCreateInfo deviceCreateInfo;
            deviceCreateInfo.setQueueCreateInfoCount(queueCreateInfos.size());
            deviceCreateInfo.setPQueueCreateInfos(queueCreateInfos.data());

            deviceCreateInfo.setEnabledExtensionCount(extensions.size());
            deviceCreateInfo.setPpEnabledExtensionNames(extensions.data());

            deviceCreateInfo.setEnabledLayerCount(layers.size());
            deviceCreateInfo.setPpEnabledLayerNames(layers.data());

            assert(physicalDevice.createDevice(&deviceCreateInfo, nullptr, &vkDevice) == vk::Result::eSuccess);

            return result;
        }
    };

    VKDevice::VKDevice(VKGpu* GPU)
        : m_private(std::make_unique<VKDevicePrivate>(GPU))
    {}
    VKDevice::~VKDevice() = default;
} // namespace RHI::Vulkan
