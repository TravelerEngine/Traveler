cmake_minimum_required(VERSION 3.25.2...3.27)

project(
  Traveler
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)
include(GenerateExportHeader)

include(CMake/Common.cmake)
include(CMake/Target.cmake)
include(CMake/ThirdParty.cmake)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_definitions(-DDEBUG)
  add_definitions(-DBIN_PATH="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

add_subdirectory(ThirdParty)
add_subdirectory(Src)
