#include <iostream>
#include "WindowApp.h"
#include "CommonUtils.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "ShadingPipeline.h"
#include "stb_image.h"
#include "Structure.h"
#include <chrono>
#include <ctime>

using namespace  std;

const int WIDTH = 640, HEIGHT = 480; // SDL窗口的宽和高
int main() {
    MicroRenderer::WindowApp app(WIDTH,HEIGHT,"first window");
    MicroRenderer::VertexData v1,v2,v3,v4,v5,v6;
    //triangle 1 绿色在前
    v1.position = glm::vec3(0,1,0); v1.color=glm::vec4 (255,128,0,0);
    v2.position = glm::vec3(1,0,0); v2.color=glm::vec4 (0,128,0,0);
    v3.position = glm::vec3(-1,-1,0); v3.color=glm::vec4 (0,128,0,0);
    //triangle 2
    v4.position = glm::vec3(-1,1,1); v4.color=glm::vec4 (0,0,128,0);
    v5.position = glm::vec3(0,-1,1); v5.color=glm::vec4 (0,0,128,0);
    v6.position = glm::vec3(1,-1,1); v6.color=glm::vec4 (0,200,128,0);

    MicroRenderer::Mesh mesh1,mesh2;
    mesh1.asTriangle(v1,v2,v3);
    mesh2.asTriangle(v4,v5,v6);
    glm::vec3 cameraPos(0,0,-2);
    glm::vec3 target(0,0,1);
    glm::vec3 worldUp(0,1,0);
    float fov = 600.0f;
    float aspectRatio = static_cast<float>(WIDTH)/static_cast<float>(HEIGHT);
    float zNear = 0.1f;
    float zFar = 100.0f;


    auto start = chrono::system_clock::now();
    while(!app.shouldWindowClose()){
        //处理事件
        auto end = chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout<<elapsed_seconds.count()<<std::endl;
        app.processEvent();
        //renderer initialize
        MicroRenderer::Renderer renderer(WIDTH,HEIGHT);
        glm::mat4 model(1.0f);
        model = MicroRenderer::MathUtils::rotationByX(model,sin(elapsed_seconds.count())*180);
        renderer.setModelMatrix(model);
        renderer.setViewMatrix(MicroRenderer::MathUtils::calViewMatrix(cameraPos,target,worldUp));
        renderer.setProjectionMatrix(MicroRenderer::MathUtils::calPerspectiveProjectionMatrix(fov,aspectRatio,zNear,zFar));
        renderer.setShader(THREE_D_SHADER);
        renderer.initShadingPipeline();
        //render
        renderer.setMeshes(std::vector<MicroRenderer::Mesh>{mesh1,mesh2});
        renderer.render();
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
