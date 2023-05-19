#pragma once

#include "RHI/Common.h"

#include <cstdint>

#include <memory>

namespace RHI {
    struct SurfaceCreateInfo {
        void* window;
    };
    class Surface {
    public:
        virtual ~Surface() = default;
    };
} // namespace RHI
