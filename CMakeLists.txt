cmake_minimum_required(VERSION 3.16)
project(SabziAM C)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable(SabziAM "${SOURCE}")

include_directories(
    "/usr/include/SDL2"
    ${CMAKE_SOURCE_DIR}/src 
)
target_link_libraries(SabziAM m SDL2 SDL2_gfx SDL2_image SDL2_ttf)