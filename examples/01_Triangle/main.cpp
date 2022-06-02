//
// Created by lm on 2022/5/24.
//

#include "WindowApp.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "stb_image.h"
using namespace  std;

const int WIDTH = 640, HEIGHT = 480; // SDL窗口的宽和高
int main() {
    MicroRenderer::WindowApp app(WIDTH,HEIGHT,"first window");
    MicroRenderer::VertexData v1,v2,v3,v4,v5,v6;
    // 直接定义已经经过视口变换后的坐标，在simple shader里，没有坐标变换，而且直接传递颜色。
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

    //camera initialize
    /**
     * 其实对于simple shader来说没有相机的概念，因为不是在三维空间中的
     * 不过为了兼容后面的一些shader，这里还是初始化一个相机
     */

    MicroRenderer::Camera camera(static_cast<float>(WIDTH),static_cast<float>(HEIGHT));
    //renderer initialize
    MicroRenderer::Renderer renderer(WIDTH,HEIGHT);
    renderer.initShadingPipeline(SIMPLE_SHADER);
    vector<MicroRenderer::Mesh> meshes{mesh};
    while(!app.shouldWindowClose()){
        //处理事件
        app.processEvent(camera);
        //render
        renderer.setMeshes(meshes);
        renderer.render(camera);
        uint8_t* pixels = renderer.getPixelBuffer();

        app.updateCanvas(pixels,WIDTH,HEIGHT, 3);
    }

    return 0;
}
