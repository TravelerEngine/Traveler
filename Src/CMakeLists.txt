add_subdirectory(Common)
add_subdirectory(RHI)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(Traveler ./main.cpp)

target_link_libraries(
  Traveler
  PUBLIC RHI
  PRIVATE Boost::program_options)
