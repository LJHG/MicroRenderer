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
        void clearBuffer();
        uint8_t* getResult();
        Shader* shader; // 直接把shader弄成public,不然又要给shading pipeline写一堆setMatrix...
    private:
        int width;
        int height;
        uint8_t* image;
        float* zBuffer;
        glm::mat4 viewPortMatrix;
        void bresenhamLineRasterization(VertexOutData& from, VertexOutData& to);
        void fillRasterization(VertexOutData& v1, VertexOutData& v2, VertexOutData& v3);
    };
}



#endif //MICRORENDERER_SHADINGPIPELINE_H
