cmake_minimum_required(VERSION 3.7)
project(gb-emu)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(gb-emu main.cpp gb.cpp cart.cpp cpu.cpp memory.cpp ram.cpp platform.cpp)

target_compile_options(gb-emu PRIVATE -Wall)

target_link_libraries(gb-emu PRIVATE ${SDL2_LIBRARIES})