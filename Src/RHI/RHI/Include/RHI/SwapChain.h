#pragma once

#include "RHI/Common.h"

#include <cstdint>

#include <memory>

namespace RHI {
    class Surface;
    struct SwapChainCreateInfo {
        std::shared_ptr<Surface> surface;
    };
    class SwapChain {
    public:
        virtual ~SwapChain() = default;
    };
} // namespace RHI
