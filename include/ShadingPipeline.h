//
// Created by lm on 2022/5/22.
//

#ifndef MICRORENDERER_SHADINGPIPELINE_H
#define MICRORENDERER_SHADINGPIPELINE_H
#include <vector>
#include "Structure.h"
#include "Shader.h"
#include "MathUtils.h"
#include <iostream>

#define SIMPLE_SHADER 1
#define LINE 1
#define FILL 2



namespace MicroRenderer{


    class ShadingPipeline {
    public:
        ShadingPipeline(int _width,int _height,Shader* _shader);
        void shade(const std::vector<VertexData>& _vertices,
                   const std::vector<unsigned int>& _indices,
                   int rasterizingMode);
        uint8_t* getResult();
    private:
        int width;
        int height;
        Shader* shader;
        uint8_t* image;
        uint8_t* imageSwap; // double buffer
        float* zBuffer;
        glm::mat4 viewPortMatrix;
        void bresenhamLineRasterization(VertexOutData& from, VertexOutData& to);
        void fillRasterization(VertexOutData& v1, VertexOutData& v2, VertexOutData& v3);
        void swapBuffer();
    };
}



#endif //MICRORENDERER_SHADINGPIPELINE_H
