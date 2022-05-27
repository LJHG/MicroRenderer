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

    MicroRenderer::Camera camera(static_cast<float>(WIDTH),static_cast<float>(HEIGHT));

    //renderer initialize
    MicroRenderer::Renderer renderer(WIDTH,HEIGHT);
    renderer.initShadingPipeline(THREE_D_SHADER);


    auto start = chrono::system_clock::now();
    while(!app.shouldWindowClose()){
        //处理事件
        auto end = chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        //std::cout<<elapsed_seconds.count()<<std::endl;
        app.processEvent(camera);

        //set view and projection matrix according to the state of camera
        renderer.setViewMatrix(MicroRenderer::MathUtils::calViewMatrix(camera.cameraPos,
                                                                       camera.target,
                                                                       camera.worldUp));
        renderer.setProjectionMatrix(MicroRenderer::MathUtils::calPerspectiveProjectionMatrix(camera.fov,
                                                                                              camera.aspectRatio,
                                                                                              camera.zNear,
                                                                                              camera.zFar));

        glm::mat4 model(1.0f);
        //model = MicroRenderer::MathUtils::rotationByX(model,sin(elapsed_seconds.count())*180);

        //render
        mesh1.setModelMatrix(model);
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
