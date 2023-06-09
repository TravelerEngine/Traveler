#include "Launcher/Launcher.h"

#include <RHI/Common.h>
#include <RHI/Device.h>
#include <RHI/Gpu.h>
#include <RHI/Instance.h>
#include <RHI/Surface.h>
#include <RHI/SwapChain.h>

#include <string>

#include <boost/program_options.hpp>

#include <iostream>

#if PLATFORM_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif PLATFORM_MACOS
    #define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace po = boost::program_options;

namespace Main {
    class LauncherPrivate {
    public:
        int width;
        int height;
        GLFWwindow* window;
    };

    Launcher::Launcher(int argc, char* argv[])
        : m_private(std::make_unique<LauncherPrivate>())
    {
        po::options_description options("options");
        options.add_options()("help", "help")("rhi", po::value<std::string>()->default_value("auto"), "RHI Type");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, options), vm);
        po::notify(vm);

        if (vm.count("help") != 0) {
            std::cout << options << std::endl;
            return;
        }

        std::string RHI {vm["rhi"].as<std::string>()};

        if (RHI == "auto") {
#if defined(__APPLE__)
            RHI = "Vulkan";
#else
            // TODO: add windows dx12 support
            RHI = "Vulkan";
#endif
        }

        // TODO: 改成加载全部插件，使用插件类型判断 RHI 是否正确。
        RHI::Instance* instance = RHI::Instance::CreateByType(RHI);
        std::cout << "Init RHI: " << RHI::ToString(instance->GetRHIType()) << std::endl;

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_private->window = glfwCreateWindow(800, 600, "Traveler", nullptr, nullptr);
#if PLATFORM_WINDOWS
        void* window = glfwGetWin32Window(m_private->window);
#elif PLATFORM_MACOS
        void* window = glfwGetCocoaWindow(m_private->window);
#else
        assert(false);
#endif
        int width;
        int height;
        glfwGetFramebufferSize(m_private->window, &width, &height);

        const uint32_t gpusCount = instance->GetGpuCount();
        assert(gpusCount > 0);

        // TODO: select the first GPU
        auto selectedGPU = instance->GetGpu(0);
        std::cout << "select GPU: " << selectedGPU->DeviceName() << std::endl;
        auto device = selectedGPU->CreateDevice();

        RHI::SurfaceCreateInfo surfaceCreateInfo;
        surfaceCreateInfo.window = window;

        auto surface = device->CreateSurface(surfaceCreateInfo);

        RHI::SwapChainCreateInfo swapChainCreateInfo;
        swapChainCreateInfo.surface = surface;
        swapChainCreateInfo.extent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height),
        };

        auto swapChain = device->CreateSwapChain(swapChainCreateInfo);
    } // namespace Main

    Launcher::~Launcher() = default;

    int Launcher::Exec()
    {
        while (glfwWindowShouldClose(m_private->window) == 0) {
            // Rending
            glfwPollEvents();
        }

        glfwDestroyWindow(m_private->window);

        return 0;
    }
} // namespace Main
