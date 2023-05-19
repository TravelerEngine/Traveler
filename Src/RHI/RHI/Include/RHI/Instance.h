#pragma once

#include "Common.h"

namespace RHI {
    class Gpu;
    class Instance {
    public:
        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        static Instance* CreateByType(const std::string& type);

        virtual RHIType GetRHIType() const = 0;

        virtual uint32_t GetGpuCount() const = 0;
        virtual std::shared_ptr<Gpu> GetGpu(uint32_t index) = 0;

    protected:
        explicit Instance() = default;
        virtual ~Instance() = default;
    };

    using RHIGetInstanceFunc = Instance* (*) ();
} // namespace RHI
