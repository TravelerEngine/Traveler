find_package(Boost REQUIRED COMPONENTS program_options)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(PLATFORM_EXT_LIBS
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation")
endif()

file(GLOB SOURCES Src/*.cpp)

AddExecutable(
    NAME Traveler
    SRC ${SOURCES}
    INC Include
    LIB RHI glfw Boost::program_options ${PLATFORM_EXT_LIBS}
)

