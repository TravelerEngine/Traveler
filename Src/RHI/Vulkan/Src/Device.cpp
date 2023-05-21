#include "RHI/Vulkan/Device.h"

#include "RHI/Vulkan/Gpu.h"
#include "RHI/Vulkan/Queue.h"
#include "RHI/Vulkan/Surface.h"
#include "RHI/Vulkan/SwapChain.h"

#include <iostream>

namespace RHI::Vulkan {
    const std::vector<const char*> enabledExtensions
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#if PLATFORM_MACOS
            "VK_KHR_portability_subset",
#endif
    };

    const std::vector<const char*> validationLayers {
#ifdef ENABLE_VALIDATION_LAYER
        "VK_LAYER_KHRONOS_validation"
#endif
    };

    class VKDevicePrivate {
    public:
        std::shared_ptr<VKGpu> m_GPU;
        uint32_t graphicsQueueFamilyIndex;
        std::vector<vk::QueueFamilyProperties> queueFamilyProperties;
        std::vector<std::shared_ptr<VKQueue>> graphicsQueues;
        std::vector<vk::CommandPool> pools;
        vk::Device vkDevice;

        explicit VKDevicePrivate(std::shared_ptr<VKGpu> GPU)
            : m_GPU(std::move(GPU))
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

            std::vector<const char*> enabledLayers;
            for (auto const& props : physicalDevice.enumerateDeviceLayerProperties()) {
                for (auto const& layer : validationLayers) {
                    if (props.layerName == layer) {
                        enabledLayers.push_back(layer);
                    }
                }
            }

            vk::PhysicalDeviceFeatures deviceFeatures;

            vk::DeviceCreateInfo deviceCreateInfo;
            deviceCreateInfo
                .setPEnabledFeatures(&deviceFeatures)
                .setQueueCreateInfoCount(queueCreateInfos.size())
                .setPQueueCreateInfos(queueCreateInfos.data())
                .setEnabledExtensionCount(enabledExtensions.size())
                .setPpEnabledExtensionNames(enabledExtensions.data())
                .setEnabledLayerCount(enabledLayers.size())
                .setPpEnabledLayerNames(enabledLayers.data());

            assert(physicalDevice.createDevice(&deviceCreateInfo, nullptr, &vkDevice) == vk::Result::eSuccess);

            graphicsQueues.resize(queueCreateInfos.size());
            for (auto const& info : queueCreateInfos) {
                vk::Queue graphicsQueue;
                vkDevice.getQueue(info.queueFamilyIndex, info.queueCount - 1, &graphicsQueue);
                graphicsQueues.emplace_back(std::make_shared<VKQueue>(graphicsQueue));
            }

            return result;
        }
    };

    VKDevice::VKDevice(std::shared_ptr<VKGpu> GPU)
        : m_private(std::make_unique<VKDevicePrivate>(std::move(GPU)))
    {}
    VKDevice::~VKDevice() = default;

    vk::Device VKDevice::GetDevice() const
    {
        return m_private->vkDevice;
    }

    std::shared_ptr<Surface> VKDevice::CreateSurface(SurfaceCreateInfo& info)
    {
        return VKSurface::Create(shared_from_this(), info);
    }

    uint32_t VKDevice::GetQueueCount() const
    {
        return m_private->graphicsQueues.size();
    }

    std::shared_ptr<Queue> VKDevice::GetQueue(uint32_t index)
    {
        return m_private->graphicsQueues[index];
    }

    std::shared_ptr<SwapChain> VKDevice::CreateSwapChain(SwapChainCreateInfo& info)
    {
        return VKSwapChain::Create(shared_from_this(), info);
    }

    std::shared_ptr<VKGpu> VKDevice::GetGPU() const
    {
        return m_private->m_GPU;
    }
} // namespace RHI::Vulkan
