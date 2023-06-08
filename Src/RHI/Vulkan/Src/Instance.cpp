#include "RHI/Vulkan/Instance.h"

#include "RHI/Vulkan/Common.h"
#include "RHI/Vulkan/Device.h"
#include "RHI/Vulkan/Gpu.h"
#include "vulkan/vulkan_handles.hpp"

#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_enums.hpp>

#include <algorithm>
#include <vector>

namespace RHI::Vulkan {
    std::vector<const char*> enabledExtensions
    {
        VK_KHR_SURFACE_EXTENSION_NAME,
            "VK_KHR_portability_enumeration",
#if PLATFORM_WINDOWS
            "VK_KHR_win32_surface",
#elif PLATFORM_MACOS
            "VK_MVK_macos_surface",
            VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
            VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
#endif
    };
#ifdef ENABLE_VALIDATION_LAYER
    std::vector<const char*> validationLayers {
        "VK_LAYER_KHRONOS_validation",
        "VK_LAYER_LUNARG_api_dump"};
#endif

    class VKInstancePrivate {
        VKInstance* parent;

    public:
        explicit VKInstancePrivate(VKInstance* instance)
            : parent(instance)
        {
        }

        ~VKInstancePrivate()
        {
            instance->destroy();
        }

        void CreateInstance()
        {
            vk::ApplicationInfo applicationInfo {"Traveler GameEngine", 1, "Traveler GameEngine", 1, VK_API_VERSION_1_3};

            uint32_t instanceLayerCount = 0;
            vk::Result result;

            std::vector<const char*> enabledLayers;
#ifdef ENABLE_VALIDATION_LAYER
            std::cout << "Instance Layers info" << std::endl;
            std::cout << "============" << std::endl;
            for (auto const& layer : vk::enumerateInstanceLayerProperties()) {
                std::cout << "\t|" << std::endl;
                std::cout << "\t|--[Layer Name]--> " << layer.layerName << std::endl;
                std::cout << "\t|--[Layer Description]--> " << layer.description << std::endl;
                for (auto const* name : validationLayers) {
                    const char* layerName = layer.layerName;
                    if (std::strcmp(name, layerName) == 0) {
                        std::cout << "\t|--[Layer Enabled]--> true" << std::endl;
                        enabledLayers.push_back(name);
                        break;
                    }
                    std::cout << "\t|--[Layer Enabled]--> false" << std::endl;
                }
            }
            std::cout << "Instance Extensions info" << std::endl;
            std::cout << "============" << std::endl;
            for (auto const& extension : vk::enumerateInstanceExtensionProperties()) {
                std::cout << "\t|" << std::endl
                          << "\t|---[Extension]--> " << extension.extensionName << std::endl;
            }
#endif

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
            result = vk::createInstance(&createInfo, nullptr, &instance);
            assert(result == vk::Result::eSuccess);

            this->instance = std::make_shared<vk::Instance>(instance);
        }

        vk::Result
        EnumeratePhysicalDevice()
        {
            auto devices = instance->enumeratePhysicalDevices();
            if (devices.empty()) {
                return vk::Result::eErrorDeviceLost;
            }

            gpus.resize(devices.size());
            std::transform(devices.begin(), devices.end(), gpus.begin(), [this](vk::PhysicalDevice device) {
                return Create<VKGpu>(parent, device);
            });

            return vk::Result::eSuccess;
        }

        std::shared_ptr<vk::Instance> instance;
        std::vector<std::shared_ptr<VKGpu>> gpus;
    };

    VKInstance::VKInstance()
        : m_private(std::make_unique<VKInstancePrivate>(this))
    {
        m_private->CreateInstance();
        m_private->EnumeratePhysicalDevice();
    }

    VKInstance::~VKInstance() = default;

    std::shared_ptr<vk::Instance> VKInstance::GetInstance() const
    {
        return m_private->instance;
    }

    uint32_t VKInstance::GetGpuCount() const
    {
        return m_private->gpus.size();
    }

    std::shared_ptr<Gpu> VKInstance::GetGpu(uint32_t index)
    {
        // FIXME: not check size.
        return m_private->gpus[index];
    }
} // namespace RHI::Vulkan

extern "C" {
RHI::Instance* RHIGetInstance()
{
    static RHI::Vulkan::VKInstance instance;
    return &instance;
}
}
