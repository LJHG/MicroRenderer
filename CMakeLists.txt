cmake_minimum_required(VERSION 3.10)
project(MicroRenderer)
set(CMAKE_CXX_STANDARD 17)


find_package(assimp REQUIRED) # 添加assimp
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
        src/Structure.cpp
        include/Structure.h
        )


target_link_libraries(MicroRenderer SDL2 assimp::assimp)
target_link_libraries(test SDL2 assimp::assimp)

add_subdirectory(./examples/01_Triangle)
add_subdirectory(./examples/02_mvpTriangle)