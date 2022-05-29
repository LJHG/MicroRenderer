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
    /*
    // 画两个三角形
    MicroRenderer::VertexData v1,v2,v3,v4,v5,v6;
    //triangle 1 绿色在前
    v1.position = glm::vec3(0,1,1); v1.color=glm::vec4 (255,128,0,0);
    v2.position = glm::vec3(1,0,1); v2.color=glm::vec4 (0,128,0,0);
    v3.position = glm::vec3(-1,-1,1); v3.color=glm::vec4 (0,128,0,0);
    //triangle 2
    v4.position = glm::vec3(-1,1,2); v4.color=glm::vec4 (0,0,128,0);
    v5.position = glm::vec3(0,-1,2); v5.color=glm::vec4 (0,0,128,0);
    v6.position = glm::vec3(1,-1,2); v6.color=glm::vec4 (0,200,128,0);

    MicroRenderer::Mesh mesh1,mesh2;
    mesh1.asTriangle(v1,v2,v3);
    mesh2.asTriangle(v4,v5,v6);

    std::vector<MicroRenderer::Mesh> meshes{mesh1,mesh2};
     */

    std::vector<MicroRenderer::Mesh> meshes = MicroRenderer::CommonUtils::loadObjModel("../assets/monkey_head/monkey_head.obj");
    MicroRenderer::Material material = meshes[0].getMaterial();
    std::cout<<"ka"<<std::endl;
    MicroRenderer::LogUtils::log(material.ka);
    std::cout<<"kd"<<std::endl;
    MicroRenderer::LogUtils::log(material.kd);
    std::cout<<"ks"<<std::endl;
    MicroRenderer::LogUtils::log(material.ks);

    //camera initialize
    MicroRenderer::Camera camera(static_cast<float>(WIDTH),static_cast<float>(HEIGHT));

    //renderer initialize
    MicroRenderer::Renderer renderer(WIDTH,HEIGHT);
    renderer.initShadingPipeline(GOURAUD_SHADER);
    renderer.addDirectionLight(DirectionLight(glm::vec3(0.2f,0.2f,0.2f),
                                              glm::vec3(0.5f,0.5f,0.5f),
                                              glm::vec3(1.0f,1.0f,1.0f),
                                              glm::vec3(-0.2f,-0.1f,-0.3f)));

    auto start = chrono::system_clock::now();
    while(!app.shouldWindowClose()){
        //处理事件
        auto end = chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        //std::cout<<elapsed_seconds.count()<<std::endl;
        app.processEvent(camera);

        //render
        renderer.setMeshes(meshes);
        renderer.render(camera);
        uint8_t* pixels = renderer.getPixelBuffer();
        app.updateCanvas(pixels,WIDTH,HEIGHT, 3);

//        MicroRenderer::Image image = MicroRenderer::CommonUtils::loadImage("../assets/1.png");
//        uint8_t pixels[WIDTH*HEIGHT*3];
//        for(int i=0;i<HEIGHT;i++){
//            for(int j=0;j<WIDTH;j++){
//                int index = (i*WIDTH+j)*3;
//                pixels[index+0] = 128;
//                pixels[index+1] = 128;
//                pixels[index+2] = 128;
//            }
//        }
//        app.updateCanvas(pixels,WIDTH,HEIGHT, 3);
    }

    return 0;
}
