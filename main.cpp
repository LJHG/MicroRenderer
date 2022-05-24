#include <iostream>
#include "WindowApp.h"
#include "CommonUtils.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "ShadingPipeline.h"
#include "stb_image.h"
using namespace  std;

const int WIDTH = 640, HEIGHT = 480; // SDL窗口的宽和高
int main() {
    MicroRenderer::WindowApp app(WIDTH,HEIGHT,"first window");
    MicroRenderer::VertexData v1,v2,v3;
    v1.position = glm::vec3(0,1,1); v1.color=glm::vec4 (255,0,0,0);
    v2.position = glm::vec3(1,0,1); v2.color=glm::vec4 (0,255,0,0);
    v3.position = glm::vec3(-1,-1,1); v3.color=glm::vec4 (0,0,255,0);
    MicroRenderer::Mesh mesh;
    mesh.asTriangle(v1,v2,v3);
    while(!app.shouldWindowClose()){
        //处理事件
        app.processEvent();
        std::vector<MicroRenderer::VertexData> vertices = mesh.getVertices();
        //vertex shader
        MicroRenderer::ShadingPipeline pipeline(WIDTH,HEIGHT,mesh.getVertices(),mesh.getIndices());
        pipeline.shade(SIMPLE_SHADER,LINE);
        uint8_t* pixels = pipeline.getResult();
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
