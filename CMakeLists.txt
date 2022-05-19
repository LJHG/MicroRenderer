cmake_minimum_required(VERSION 3.10)
project(MicroRenderer)

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/external/include)
link_directories(${PROJECT_SOURCE_DIR}/external/libs)

find_package(SDL2 REQUIRED)
add_executable(MicroRenderer main.cpp src/WindowApp.cpp include/WindowApp.h src/CommonUtils.cpp include/CommonUtils.h external/include/stb_image.h)
target_link_libraries(MicroRenderer SDL2)