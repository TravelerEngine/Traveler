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
        }

        ~VKInstancePrivate()
        {
            instance->destroy();
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
        std::vector<std::shared_ptr<VKGpu>> gpus;
    };

    VKInstance::VKInstance()
        : m_private(std::make_unique<VKInstancePrivate>(this))
    {
        m_private->CreateInstance();
        m_private->EnumeratePhysicalDevice();
    }

    VKInstance::~VKInstance() = default;

    std::shared_ptr<vk::Instance> VKInstance::GetInstance()
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
