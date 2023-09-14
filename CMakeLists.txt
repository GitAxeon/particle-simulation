cmake_minimum_required(VERSION 3.24)
project(particle-simulation)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)

file(
    GLOB_RECURSE source-files
    "src/*.cpp"
    "src/*.hpp"
)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

# Compile imgui
file(
    GLOB imgui-sources
    "vendor/imgui/*.cpp"
    "vendor/imgui/backends/imgui_impl_sdlrenderer3.cpp"
    "vendor/imgui/backends/imgui_impl_sdl3.cpp"     
)
add_library(imgui STATIC ${imgui-sources})
target_include_directories(imgui PUBLIC vendor/imgui/ vendor/SDL/include/)

# Add sources and whatnot
add_executable(particle-simulation ${source-files})

target_include_directories(
    particle-simulation PUBLIC 
    vendor/SDL/include/
    vendor/imgui/
    vendor/imgui/backends/
)

target_link_libraries(
    particle-simulation PRIVATE
    SDL3::SDL3
    imgui
)