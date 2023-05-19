#pragma once

#include "RHI/Common.h"

#include <cstdint>

#include <memory>

namespace RHI {
    class Surface;
    struct SwapChainCreateInfo {
        std::shared_ptr<Surface> surface;
        struct Extent {
            uint32_t width;
            uint32_t height;
        } extent;
    };
    class SwapChain {
    public:
        virtual ~SwapChain() = default;
    };
} // namespace RHI
