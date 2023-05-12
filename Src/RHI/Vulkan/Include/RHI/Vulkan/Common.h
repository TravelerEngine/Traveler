#pragma once

#include <vulkan/vulkan.hpp>

struct LayerProperties {
    vk::LayerProperties properties;
    std::vector<vk::ExtensionProperties> extensions;
};
