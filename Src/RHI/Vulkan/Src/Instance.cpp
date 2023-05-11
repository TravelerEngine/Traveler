#include "RHI/Vulkan/Instance.h"

#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_enums.hpp>

#include <algorithm>
#include <vector>

namespace RHI::Vulkan {
std::vector<const char *> enabledExtensions{
    VK_KHR_SURFACE_EXTENSION_NAME,
    "VK_KHR_portability_enumeration",
};
std::vector<const char *> enabledLayers{"VK_LAYER_KHRONOS_validation", "VK_LAYER_LUNARG_api_dump"};

struct LayerProperties
{
  vk::LayerProperties properties;
  std::vector<vk::ExtensionProperties> extensions;
};

class VKInstancePrivate
{
 public:
  VKInstancePrivate()
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

    for (auto &layerProperty : instanceLayers) {
      LayerProperties layerProps;
      layerProps.properties = layerProperty;

      std::cout << layerProperty.description << std::endl
                << "\t|\n\t|---[Layer Name]--> " << layerProperty.layerName << std::endl;

      result = GetExtensionProperties(layerProps);
      layerProperties.push_back(layerProps);
    }

    CreateInstance();
  }

  ~VKInstancePrivate() { instance.destroy(); }

  // TODO: support GPU
  vk::Result GetExtensionProperties(LayerProperties &layerProperties)
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
    vk::ApplicationInfo applicationInfo;
    applicationInfo.pApplicationName = "Traveler GameEngine";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "Traveler GameEngine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_3;

    vk::InstanceCreateInfo createInfo = {};
    createInfo.pApplicationInfo = &applicationInfo;

    createInfo.enabledExtensionCount = enabledExtensions.size();
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();

    createInfo.enabledLayerCount = enabledLayers.size();
    createInfo.ppEnabledLayerNames = enabledLayers.data();

#if defined(__APPLE__)
    createInfo.flags = vk::InstanceCreateFlags(VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR);
#endif

    vk::Result result = vk::createInstance(&createInfo, nullptr, &instance);
    assert(result == vk::Result::eSuccess);
  }

  vk::Instance instance;
  std::vector<LayerProperties> layerProperties;
};

VKInstance::VKInstance()
    : m_private(std::make_unique<VKInstancePrivate>())
{
}

VKInstance::~VKInstance() {}

vk::Instance VKInstance::GetInstance() const
{
  return m_private->instance;
}
}  // namespace RHI::Vulkan

extern "C" {
RHI::Instance *RHIGetInstance()
{
  static RHI::Vulkan::VKInstance instance;
  return &instance;
}
}
