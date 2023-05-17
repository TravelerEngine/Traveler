#include "RHI/Vulkan/Surface.h"

namespace RHI::Vulkan {
    class SurfacePrivate {
        std::shared_ptr<VKDevice> device;
        explicit SurfacePrivate(std::shared_ptr<VKDevice> device)
            : device(std::move(device))
        {}

        ~SurfacePrivate() = default;
    };
    Surface::Surface(std::shared_ptr<VKDevice> device)
        : m_private(std::make_shared<SurfacePrivate>(std::move(device)))
    {}
    Surface::~Surface() = default;

} // namespace RHI::Vulkan
