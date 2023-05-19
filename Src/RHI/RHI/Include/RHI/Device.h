#pragma once

#include "RHI/Common.h"

#include <cstdint>

#include <memory>

namespace RHI {
    struct SwapChainCreateInfo;
    struct SurfaceCreateInfo;
    class Queue;
    class Surface;
    class SwapChain;
    class Device {
    public:
        virtual ~Device() = default;
        virtual std::shared_ptr<Surface> CreateSurface(SurfaceCreateInfo& info) = 0;

        virtual uint32_t GetQueueCount() const = 0;
        virtual std::shared_ptr<Queue> GetQueue(uint32_t index) = 0;
        virtual std::shared_ptr<SwapChain> CreateSwapChain(SwapChainCreateInfo& info) = 0;
    };
} // namespace RHI
