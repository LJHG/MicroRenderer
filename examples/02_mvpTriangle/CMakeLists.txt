cmake_minimum_required(VERSION 3.10)
project(02_mvpTriangle)
set(CMAKE_CXX_STANDARD 17)

add_executable(02_mvpTriangle
        main.cpp
        ../../src/WindowApp.cpp
        ../../include/WindowApp.h
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
        ../../src/Camera.cpp
        ../../include/Camera.h
        )

target_link_libraries(02_mvpTriangle SDL2)