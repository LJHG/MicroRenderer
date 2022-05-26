//
// Created by lm on 2022/5/20.
//

#ifndef MICRORENDERER_RENDERER_H
#define MICRORENDERER_RENDERER_H

#include "glm/glm.hpp"
#include "ShadingPipeline.h"
#include "Shader.h"
#include "Structure.h"

#define SIMPLE_SHADER 1
#define THREE_D_SHADER 2

namespace MicroRenderer{
    class Renderer{
    public:
        //initialize stage functions -> 其实可以全部写到构造函数里,emmm
        Renderer(int _width, int _height);
        void setViewMatrix(const glm::mat4& v);
        void setProjectionMatrix(const glm::mat4& p);
        void initShadingPipeline(int shadingMode);
        //render
        void setMeshes(const std::vector<Mesh>& _meshes);
        void render();
        uint8_t* getPixelBuffer();
    private:
        int width;
        int height;
        std::vector<Mesh> meshes;
        ShadingPipeline* shadingPipeline;
        uint8_t* pixelBuffer;
        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    };

}

#endif //MICRORENDERER_RENDERER_H
