//
// Created by Zach Lee on 2022/4/4.
//

#if PLATFORM_WINDOWS
    #include <RHI/SwapChain.h>
    #include <Windows.h>
    #define VK_USE_PLATFORM_WIN32_KHR
    #include <vulkan/vulkan.hpp>

namespace RHI::Vulkan {
    vk::SurfaceKHR CreateNativeSurface(const vk::Instance& instance, const SurfaceCreateInfo& createInfo)
    {
        vk::Win32SurfaceCreateInfoKHR surfaceInfo {};
        surfaceInfo.setHwnd((HWND) createInfo.window)
            .setHinstance(GetModuleHandle(0));
        vk::SurfaceKHR surface = VK_NULL_HANDLE;
        assert(instance.createWin32SurfaceKHR(&surfaceInfo, nullptr, &surface) == vk::Result::eSuccess);
        return surface;
    }
} // namespace RHI::Vulkan
#endif
