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

        explicit VKGpuPrivate(VKInstance* instance, vk::PhysicalDevice device)
            : instance(instance)
            , device(device)
        {
            GetExtensionProperties();
        }

        vk::Result GetExtensionProperties() const
        {
            std::cout << "Devices extensions" << std::endl;
            std::cout << "================" << std::endl;

            vk::Result result;
            for (const auto& props : instance->GetLayerProperties()) {
                auto properties = device.enumerateDeviceExtensionProperties();
                std::cout << props.properties.description << std::endl
                          << "\t|\n\t|---[Layer Name]--> " << props.properties.layerName << std::endl;

                for (auto ext : properties) {
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

    std::shared_ptr<VKDevice> VKGpu::CreateDevice()
    {
        return VKDevice::Create(shared_from_this());
    }

    const vk::PhysicalDevice& VKGpu::GetVkPhysicalDevice() const
    {
        return m_private->device;
    }

    std::string VKGpu::DeviceName() const
    {
        auto props = m_private->device.getProperties();
        return props.deviceName;
    }
} // namespace RHI::Vulkan
