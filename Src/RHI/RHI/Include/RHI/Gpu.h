#pragma once

#include "RHI/Common.h"

#include <cstdint>

#include <memory>

namespace RHI {
    class Device;
    class Gpu {
    public:
        virtual ~Gpu() = default;
        virtual std::shared_ptr<Device> CreateDevice() = 0;
        virtual std::string DeviceName() const = 0;
    };
} // namespace RHI
