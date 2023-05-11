file(GLOB SOURCES Src/*.cpp)

addlibrary(
  NAME
    RHI-Vulkan
  TYPE
    SHARED
  SRC
    ${SOURCES}
  PUBLIC_INC
    Include
  LIB
    RHI
    VulkanSDK
)
