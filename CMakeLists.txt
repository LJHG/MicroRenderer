cmake_minimum_required(VERSION 3.10)
project(MicroRenderer)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/external/include)
link_directories(${PROJECT_SOURCE_DIR}/external/libs)

add_executable(MicroRenderer
        main.cpp
        src/WindowApp.cpp
        include/WindowApp.h
        src/CommonUtils.cpp
        include/CommonUtils.h
        external/include/stb_image.h
        include/Renderer.h
        src/Renderer.cpp
        src/MathUtils.cpp
        include/MathUtils.h
        src/Structure.cpp
        include/Structure.h
        src/ShadingPipeline.cpp
        include/ShadingPipeline.h
        src/Shader.cpp
        include/Shader.h
        src/LogUtils.cpp
        include/LogUtils.h
        src/Camera.cpp
        include/Camera.h)

add_executable(test
        test.cpp
        src/LogUtils.cpp
        include/LogUtils.h
        )


target_link_libraries(MicroRenderer SDL2)

add_subdirectory(./examples/01_Triangle)