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
        VKInstance* instance;
        vk::PhysicalDevice device;
        std::vector<LayerProperties> layerProperties;

        explicit VKGpuPrivate(VKInstance* instance, vk::PhysicalDevice device)
            : instance(instance)
            , device(device)
        {
            GetExtensionProperties();
        }

        vk::Result GetExtensionProperties()
        {
            std::cout << "Devices extensions" << std::endl;
            std::cout << "================" << std::endl;

            vk::Result result;
            for (const auto& props : instance->GetLayerProperties()) {
                uint32_t extensionCount;
                LayerProperties properties;
                properties.properties = props.properties.layerName;
                device.enumerateDeviceExtensionProperties(properties.properties.layerName, &extensionCount, nullptr);
                if (extensionCount == 0u) {
                    continue;
                }
                properties.extensions.resize(extensionCount);
                device.enumerateDeviceExtensionProperties(properties.properties.layerName, &extensionCount, properties.extensions.data());
                layerProperties.push_back(properties);

                std::cout << properties.properties.description << std::endl
                          << "\t|\n\t|---[Layer Name]--> " << properties.properties.layerName << std::endl;

                for (auto ext : properties.extensions) {
                    std::cout << "\t\t|" << std::endl
                              << "\t\t|---[Layer Extension]--> " << ext.extensionName << std::endl;
                }
            }

            return result;
        }

        ~VKGpuPrivate() = default;
    };

    VKGpu::VKGpu(VKInstance* instance, vk::PhysicalDevice device)
        : m_private(std::make_unique<VKGpuPrivate>(instance, device))
    {
    }

    VKGpu::~VKGpu() = default;

    VKDevice* VKGpu::CreateDevice()
    {
        return new VKDevice(this);
    }

    const vk::PhysicalDevice& VKGpu::GetVkPhysicalDevice() const
    {
        return m_private->device;
    }
} // namespace RHI::Vulkan
