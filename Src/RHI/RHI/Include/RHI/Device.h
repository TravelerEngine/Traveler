#pragma once

#include "RHI/Common.h"

#include <cstdint>

#include <memory>

namespace RHI {
    class Surface;
    class Device {
    public:
        virtual ~Device() = default;
        virtual std::shared_ptr<Surface> CreateSurface() = 0;
    };
} // namespace RHI
