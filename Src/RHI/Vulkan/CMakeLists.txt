set(SOURCES
    Src/Device.cpp
    Src/Gpu.cpp
    Src/Instance.cpp
    Src/Queue.cpp
    Src/Surface.cpp
    Src/SwapChain.cpp
    Src/Texture.cpp
    Src/TextureView.cpp
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set(PLATFORM_SOURCES Src/Platform/Win32Surface.cpp)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(PLATFORM_SOURCES Src/Platform/MacosSurface.mm)
  set(PLATFORM_EXT_LIBS "-framework Cocoa" "-framework IOKit"
                        "-framework CoreFoundation")
endif()

addlibrary(
  NAME RHI-Vulkan
  TYPE SHARED
  SRC ${SOURCES} ${PLATFORM_SOURCES}
  PUBLIC_INC Include
  LIB RHI VulkanSDK ${PLATFORM_EXT_LIBS}
)
