cmake_minimum_required(VERSION 3.7)
project(gb-emu)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(gb-emu main.cpp gb.cpp cart.cpp)

target_compile_options(gb-emu PRIVATE -Wall)

target_link_libraries(gb-emu PRIVATE ${SDL2_LIBRARIES})