#include "RHI/Vulkan/Surface.h"
#include "RHI/Vulkan/Device.h"

namespace RHI::Vulkan {
    class VKSurfacePrivate {
    public:
        std::shared_ptr<VKDevice> device;
        explicit VKSurfacePrivate(std::shared_ptr<VKDevice> device)
            : device(std::move(device))
        {}

        ~VKSurfacePrivate() = default;
    };
    VKSurface::VKSurface(std::shared_ptr<VKDevice> device)
        : m_private(std::make_shared<VKSurfacePrivate>(std::move(device)))
    {}
    VKSurface::~VKSurface() = default;

} // namespace RHI::Vulkan
