cmake_minimum_required(VERSION 3.10)
project(01_Triangle)
set(CMAKE_CXX_STANDARD 17)

add_executable(01_Triangle
        main.cpp
        ../../src/WindowApp.cpp
        ../../include/WindowApp.h
        ../../src/CommonUtils.cpp
        ../../include/CommonUtils.h
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
        ../../src/Camera.cpp
        ../../include/Camera.h
        )

target_link_libraries(01_Triangle SDL2 assimp::assimp)