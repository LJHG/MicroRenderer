//
// Created by lm on 2022/5/24.
//

#include "WindowApp.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "ShadingPipeline.h"
#include "stb_image.h"
using namespace  std;

const int WIDTH = 640, HEIGHT = 480; // SDL窗口的宽和高
int main() {
    MicroRenderer::WindowApp app(WIDTH,HEIGHT,"first window");
    MicroRenderer::VertexData v1,v2,v3,v4,v5,v6;
    //triangle 1 彩色在前
    v1.position = glm::vec3(0,1,0); v1.color=glm::vec4 (255,0,0,0);
    v2.position = glm::vec3(1,0,0); v2.color=glm::vec4 (0,255,0,0);
    v3.position = glm::vec3(-1,-1,0); v3.color=glm::vec4 (0,0,255,0);
    //triangle 2
    v4.position = glm::vec3(-1,1,1); v4.color=glm::vec4 (0,0,128,0);
    v5.position = glm::vec3(0,-1,1); v5.color=glm::vec4 (0,0,128,0);
    v6.position = glm::vec3(1,-1,1); v6.color=glm::vec4 (0,0,128,0);

    MicroRenderer::Mesh mesh;
    mesh.setVertices(std::vector<MicroRenderer::VertexData>{v1,v2,v3,v4,v5,v6});
    mesh.setIndices(std::vector<unsigned int>{0,1,2,3,4,5});
    while(!app.shouldWindowClose()){
        //处理事件
        app.processEvent();
        std::vector<MicroRenderer::VertexData> vertices = mesh.getVertices();
        //vertex shader
        MicroRenderer::ShadingPipeline pipeline(WIDTH,HEIGHT,mesh.getVertices(),mesh.getIndices());
        pipeline.shade(SIMPLE_SHADER,FILL);
        uint8_t* pixels = pipeline.getResult();
        app.updateCanvas(pixels,WIDTH,HEIGHT, 3);
    }

    return 0;
}
