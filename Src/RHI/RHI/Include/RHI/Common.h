#pragma once

#include <cstdint>
#include <iostream>
#include <type_traits>

namespace RHI {
    using EnumType = uint32_t;

    enum class RHIType : EnumType {
        Vulkan,
    };

    constexpr std::string_view ToString(RHIType value)
    {
        switch (value) {
            case RHIType::Vulkan:
                return "Vulkan";
            default:
                return "Unknown";
        }
    }

    struct PixelFormat {
    };

    struct Extent {
        uint32_t width;
        uint32_t height;
    };

    template <typename T, typename... Args>
    [[nodiscard]] inline static std::shared_ptr<T> Create(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
} // namespace RHI
