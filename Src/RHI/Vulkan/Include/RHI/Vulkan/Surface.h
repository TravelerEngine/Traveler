#pragma once

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class VKDevice;
    class SurfacePrivate;
    class Surface {
        std::shared_ptr<SurfacePrivate> m_private;

    public:
        explicit Surface(std::shared_ptr<VKDevice> device);
        ~Surface();
    };
} // namespace RHI::Vulkan
