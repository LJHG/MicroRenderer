cmake_minimum_required(VERSION 3.10)
project(03_mary)
set(CMAKE_CXX_STANDARD 17)

add_executable(03_mary
        main.cpp
        ../../src/WindowApp.cpp
        ../../include/WindowApp.h
        ../../src/CommonUtils.cpp
        ../../include/CommonUtils.h
        ../../external/include/stb_image.h
        ../../include/Renderer.h
        ../../src/Renderer.cpp
        ../../src/MathUtils.cpp
        ../../include/MathUtils.h
        ../../src/Structure.cpp
        ../../include/Structure.h
        ../../src/ShadingPipeline.cpp
        ../../include/ShadingPipeline.h
        ../../src/Shader.cpp
        ../../include/Shader.h
        ../../src/LogUtils.cpp
        ../../include/LogUtils.h
        ../../src/Camera.cpp
        ../../include/Camera.h
        ../../src/Light.cpp
        ../../include/Light.h)

target_link_libraries(03_mary SDL2 assimp::assimp)