#include "RHI/Vulkan/Instance.h"

#include "RHI/Vulkan/Common.h"
#include "RHI/Vulkan/Device.h"
#include "RHI/Vulkan/Gpu.h"

#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_enums.hpp>

#include <algorithm>
#include <vector>

namespace RHI::Vulkan {
    std::vector<const char*> enabledExtensions {
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_KHR_portability_enumeration",
    };
    std::vector<const char*> enabledLayers {
#ifdef ENABLE_VALIDATION_LAYERS
        "VK_LAYER_KHRONOS_validation",
        "VK_LAYER_LUNARG_api_dump"
#endif
    };

    class VKInstancePrivate {
        VKInstance* parent;

    public:
        explicit VKInstancePrivate(VKInstance* instance)
            : parent(instance)
        {
            uint32_t instanceLayerCount = 0;
            vk::Result result;

            result = vk::enumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
            assert(result == vk::Result::eSuccess);

            std::vector<vk::LayerProperties> instanceLayers(instanceLayerCount);
            result = vk::enumerateInstanceLayerProperties(&instanceLayerCount, instanceLayers.data());
            assert(result == vk::Result::eSuccess);

            std::cout << "Instanced Layers" << std::endl;
            std::cout << "=================" << std::endl;

            for (auto& layerProperty : instanceLayers) {
                LayerProperties layerProps;
                layerProps.properties = layerProperty;

                std::cout << layerProperty.description << std::endl
                          << "\t|\n\t|---[Layer Name]--> " << layerProperty.layerName << std::endl;

                result = GetExtensionProperties(layerProps);
                layerProperties.push_back(layerProps);
            }
        }

        ~VKInstancePrivate()
        {
            instance->destroy();
        }

        static vk::Result GetExtensionProperties(LayerProperties& layerProperties)
        {
            uint32_t extensionCount = 0;
            vk::Result result;
            result = vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
            assert(result == vk::Result::eSuccess);

            std::vector<vk::ExtensionProperties> extensions(extensionCount);
            result = vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
            assert(result == vk::Result::eSuccess);

            layerProperties.extensions = extensions;
            for (auto ext : extensions) {
                std::cout << "\t\t|" << std::endl
                          << "\t\t|---[Layer Extension]--> " << ext.extensionName << std::endl;
            }

            return result;
        }

        void CreateInstance()
        {
            vk::ApplicationInfo applicationInfo {"Traveler GameEngine", 1, "Traveler GameEngine", 1, VK_API_VERSION_1_3};

            vk::InstanceCreateInfo createInfo
            {
#if defined(__APPLE__)
                vk::InstanceCreateFlags(VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR),
#else

                vk::InstanceCreateFlags(),
#endif
                    &applicationInfo,
                    static_cast<uint32_t>(enabledLayers.size()),
                    enabledLayers.data(),
                    static_cast<uint32_t>(enabledExtensions.size()),
                    enabledExtensions.data(),
                    nullptr
            };

            vk::Instance instance;
            vk::Result result = vk::createInstance(&createInfo, nullptr, &instance);
            assert(result == vk::Result::eSuccess);

            this->instance = std::make_shared<vk::Instance>(instance);
        }

        vk::Result EnumeratePhysicalDevice()
        {
            auto devices = instance->enumeratePhysicalDevices();
            if (devices.empty()) {
                return vk::Result::eErrorDeviceLost;
            }

            gpus.resize(devices.size());
            std::transform(devices.begin(), devices.end(), gpus.begin(), [this](vk::PhysicalDevice device) {
                return VKGpu::Create(parent, device);
            });

            return vk::Result::eSuccess;
        }

        std::shared_ptr<vk::Instance> instance;
        std::vector<LayerProperties> layerProperties;
        std::vector<std::shared_ptr<VKGpu>> gpus;
    };

    VKInstance::VKInstance()
        : m_private(std::make_unique<VKInstancePrivate>(this))
    {
        m_private->CreateInstance();
        m_private->EnumeratePhysicalDevice();
        auto selectedGPU = *m_private->gpus.begin();
        std::cout << "select GPU: " << selectedGPU->DeviceName() << std::endl;
    }

    VKInstance::~VKInstance() = default;

    std::shared_ptr<vk::Instance> VKInstance::GetInstance()
    {
        return m_private->instance;
    }

    std::vector<LayerProperties> VKInstance::GetLayerProperties()
    {
        return m_private->layerProperties;
    }
} // namespace RHI::Vulkan

extern "C" {
RHI::Instance* RHIGetInstance()
{
    static RHI::Vulkan::VKInstance instance;
    return &instance;
}
}
