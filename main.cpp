#include <iostream>
#include "WindowApp.h"
#include "CommonUtils.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "ShadingPipeline.h"
#include "stb_image.h"
#include "Structure.h"
#include <chrono>
#include "Camera.h"

using namespace  std;

const int WIDTH = 640, HEIGHT = 480; // SDL窗口的宽和高
int main() {
    MicroRenderer::WindowApp app(WIDTH,HEIGHT,"first window");

    // mesh initialize
    std::vector<MicroRenderer::Mesh> meshes = MicroRenderer::CommonUtils::loadObjModel("../assets/rock/rock.obj");

    //camera initialize
    MicroRenderer::Camera camera(static_cast<float>(WIDTH),static_cast<float>(HEIGHT));

    //renderer initialize
    MicroRenderer::Renderer renderer(WIDTH,HEIGHT);
    renderer.initShadingPipeline(PHONG_SHADER);
    renderer.addDirectionLight(new DirectionLight(glm::vec3(0.2f,0.2f,0.2f),
                                              glm::vec3(0.5f,0.5f,0.5f),
                                              glm::vec3(0.5f,0.5f,0.5f),
                                              glm::vec3(-0.2f,-0.1f,-0.3f)));

    glm::vec3 pointLightPos = glm::vec3(0.7f,1.2f,-3.0f);
    PointLight light1(glm::vec3(0.2f,0.2f,0.2f),
                      glm::vec3(0.5f,0.5f,0.5f),
                      glm::vec3(1.0f,1.0f,1.0f),
                      pointLightPos);

    renderer.addPointLight(&light1);
    // draw the point light
    MicroRenderer::Mesh pointLight1;
    pointLight1.asCube(pointLightPos,0.2f, MicroRenderer::Material(glm::vec3(0.1f,0.1f,0.1f),
                                                                                    glm::vec3(1000.0f,1000.0f,1000.0f),
                                                                                    glm::vec3(0.1f,0.1f,0.1f),
                                                                                    32.0f));
    meshes.push_back(pointLight1);

    auto start = chrono::system_clock::now();
    while(!app.shouldWindowClose()){
        //处理事件
        auto end = chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        glm::vec3 lightOffset = glm::vec3(3*sin(elapsed_seconds.count()),0,3*cos(elapsed_seconds.count()));
        //std::cout<<elapsed_seconds.count()<<std::endl;
        light1.setLightPos(pointLightPos + lightOffset);
        MicroRenderer::Mesh& pointLightMesh = meshes.back();
        pointLightMesh.asCube(pointLightPos + lightOffset,0.2f, MicroRenderer::Material(glm::vec3(0.1f,0.1f,0.1f),
                                                                          glm::vec3(1000.0f,1000.0f,1000.0f),
                                                                          glm::vec3(0.1f,0.1f,0.1f),
                                                                          32.0f));
        app.processEvent(camera);

        //render
        renderer.setMeshes(meshes);
        renderer.render(camera);
        uint8_t* pixels = renderer.getPixelBuffer();
        app.updateCanvas(pixels,WIDTH,HEIGHT, 3);

    }

    return 0;
}
