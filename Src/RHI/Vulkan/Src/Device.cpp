#include "RHI/Vulkan/Device.h"

#include "RHI/Vulkan/Gpu.h"
#include "RHI/Vulkan/Queue.h"
#include "vulkan/vulkan_structs.hpp"

#include <iostream>

namespace RHI::Vulkan {
    const std::vector<const char*> extensions
    {
#if PLATFORM_MACOS
        "VK_KHR_portability_subset"
#endif
    };

    const std::vector<const char*> layers {
#ifdef ENABLE_VALIDATION_LAYERS
        "VK_LAYER_KHRONOS_validation"
#endif
    };

    class VKDevicePrivate {
    public:
        VKGpu* m_GPU;
        uint32_t graphicsQueueFamilyIndex;
        std::vector<vk::QueueFamilyProperties> queueFamilyProperties;
        std::vector<std::shared_ptr<VKQueue>> graphicsQueues;
        std::vector<vk::CommandPool> pools;
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
            queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

            assert(!queueFamilyProperties.empty());

            std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
            for (unsigned int i = 0; i < queueFamilyProperties.size(); ++i) {
                if (queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                    float priority = 1.0f;
                    vk::DeviceQueueCreateInfo info;
                    info.setQueueFamilyIndex(i)
                        .setQueueCount(queueFamilyProperties[i].queueCount)
                        .setPQueuePriorities(&priority);

                    queueCreateInfos.push_back(info);
                }
            }

            assert(!queueCreateInfos.empty());

            vk::PhysicalDeviceFeatures deviceFeatures;

            vk::DeviceCreateInfo deviceCreateInfo;
            deviceCreateInfo
                .setPEnabledFeatures(&deviceFeatures)
                .setQueueCreateInfoCount(queueCreateInfos.size())
                .setPQueueCreateInfos(queueCreateInfos.data())
                .setEnabledExtensionCount(extensions.size())
                .setPpEnabledExtensionNames(extensions.data())
                .setEnabledLayerCount(layers.size())
                .setPpEnabledLayerNames(layers.data());

            assert(physicalDevice.createDevice(&deviceCreateInfo, nullptr, &vkDevice) == vk::Result::eSuccess);

            graphicsQueues.resize(queueCreateInfos.size());
            for (auto const& info : queueCreateInfos) {
                vk::Queue graphicsQueue;
                vkDevice.getQueue(info.queueFamilyIndex, info.queueCount, &graphicsQueue);
                graphicsQueues.emplace_back(std::make_shared<VKQueue>(graphicsQueue));
            }

            return result;
        }
    };

    VKDevice::VKDevice(VKGpu* GPU)
        : m_private(std::make_unique<VKDevicePrivate>(GPU))
    {}
    VKDevice::~VKDevice() = default;
} // namespace RHI::Vulkan
