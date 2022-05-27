//
// Created by lm on 2022/5/22.
//

#include "ShadingPipeline.h"

namespace MicroRenderer{
   ShadingPipeline::ShadingPipeline(int _width, int _height, Shader* _shader) {
       width = _width;
       height = _height;
       shader = _shader;
       image = (uint8_t*) malloc(sizeof(uint8_t)*width*height*3);
       zBuffer = (float*)malloc(sizeof(float)*width*height);
       //initialize buffer (avoid sparkle in the beginning)
       clearBuffer();
       viewPortMatrix = MathUtils::calViewPortMatrix(0,0,width,height);
   }

    void ShadingPipeline::shade(const std::vector<VertexData>& _vertices,
                                const std::vector<unsigned int>& _indices,
                                int rasterizingMode) {
        //according to indices, every 3 indices organize as a triangle, len(indices) could be greater than len(_vertices)

        VertexData v1,v2,v3;
        VertexOutData v1o,v2o,v3o;
        for(int i=0;i<_indices.size()/3;i++){
            v1 = _vertices[_indices[i*3+0]];
            v2 = _vertices[_indices[i*3+1]];
            v3 = _vertices[_indices[i*3+2]];
            //vertex shader
            v1o = shader->vertexShader(v1);
            v2o = shader->vertexShader(v2);
            v3o = shader->vertexShader(v3);

            // division (好像很有必要写...)
            v1o.position = v1o.position / v1o.position[3];
            v2o.position = v2o.position / v2o.position[3];
            v3o.position = v3o.position / v3o.position[3];

            //view port transformation
            v1o.position = viewPortMatrix * v1o.position;
            v2o.position = viewPortMatrix * v2o.position;
            v3o.position = viewPortMatrix * v3o.position;

            //rasterization
            // the triangle will appear upside down because it goes like ➡️ x ⬇️ y, but never mind...
            if(rasterizingMode == LINE){
                // BresenHam line drawing algorithm
                bresenhamLineRasterization(v1o,v2o);
                bresenhamLineRasterization(v1o,v3o);
                bresenhamLineRasterization(v3o,v2o);
            }else if(rasterizingMode == FILL){
                // bounding box inside triangle fill algorithm -> games101 assignment2 and assignment3
                fillRasterization(v1o,v2o,v3o);
            }
        }
   }

    void ShadingPipeline::bresenhamLineRasterization(VertexOutData &from, VertexOutData &to) {
        // ref: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
        int x0 = static_cast<int>(from.position[0]);
        int y0 = static_cast<int>(from.position[1]);
        int x1 = static_cast<int>(to.position[0]);
        int y1 = static_cast<int>(to.position[1]);


        int dx = abs(x1-x0);
        int sx = x0 < x1? 1:-1;
        int dy = -abs(y1-y0);
        int sy = y0<y1 ? 1:-1;
        int error = dx + dy;

        int periodLen = abs(x1-x0);
        while(true){
            //plot x0 y0
            float t = 1- static_cast<float>(abs(x1-x0))/static_cast<float>(periodLen);
            VertexOutData tmp = MathUtils::lerp(from,to,t);
            //fragment shader
            glm::vec4 color = shader->fragmentShader(tmp);
            int index = (y0*width+x0)*3;
            image[index +0] = static_cast<int>(color[0]);
            image[index +1] = static_cast<int>(color[1]);
            image[index +2] = static_cast<int>(color[2]);

            if(x0 == x1 && y0 == y1){
                break;
            }
            int e2 = 2*error;
            if(e2 >= dy){
                if( x0 == x1) break;
                error = error + dy;
                x0 = x0 + sx;
            }
            if(e2 <= dx){
                if(y0 == y1) break;
                error = error + dx;
                y0 = y0 + sy;
            }
        }
   }

    void ShadingPipeline::fillRasterization(VertexOutData &v1, VertexOutData &v2, VertexOutData &v3) {
       // I don't know name for this algorithm
       // ref: GAMES101 assignment2: https://www.ljhblog.top/CG/GAMES101/assignment2.html
       float x1 = v1.position[0]; float y1 = v1.position[1]; float z1 = v1.position[2];
       float x2 = v2.position[0]; float y2 = v2.position[1]; float z2 = v2.position[2];
       float x3 = v3.position[0]; float y3 = v3.position[1]; float z3 = v3.position[2];

       /**
        * 关于clip是否应该在光栅化时做的问题
        * 一般来说，clip好像应该在做光栅化前来做，但是如果直接在光栅化时做会十分方便...
        * 这里我在光栅化时作了两个clip:
        * 1. 一个判断z，如果z不在[-1,1]内，那么就说明不再视线范围内，直接不画
        * 2. 另一个对left right bottom top 做一个裁剪，不去管屏幕空间外的像素了
        */
       // clip1
       if(z1<-1.0f || z1 >1.0f || z2<-1.0f || z2 > 1.0f || z3<-1.0f || z3>1.0f){
           //out of depth range, clip
           return;
       }

       // get bounding box of the triangle
       int left = static_cast<int>(std::min(std::min(x1,x2),x3));
       int bottom = static_cast<int>(std::min(std::min(y1,y2),y3));
       int right = static_cast<int>(std::max(std::max(x1,x2),x3)) + 1; //ceil
       int top = static_cast<int>(std::max(std::max(y1,y2),y3)) + 1; //ceil

       // clip2
       left = std::max(left,0);
       bottom = std::max(bottom,0);
       right = std::min(right,width);
       top = std::min(top,height);

       for(int x = left;x<=right;x++){
           for(int y=bottom;y<=top;y++){
               if(MathUtils::insideTriangle(static_cast<float>(x),static_cast<float>(y),x1,y1,x2,y2,x3,y3)){
                   VertexOutData tmp = MathUtils::barycentricLerp(x,y,v1,v2,v3);
                   int index = y*width+x;
                   if(tmp.position[2] < zBuffer[index]){
                       zBuffer[index] = tmp.position[2];
                       //fragment shader
                       glm::vec4 color = shader->fragmentShader(tmp);
                       int colorIndex =  index*3; //multiply channel
                       image[colorIndex +0] = static_cast<int>(color[0]);
                       image[colorIndex +1] = static_cast<int>(color[1]);
                       image[colorIndex +2] = static_cast<int>(color[2]);
                   }
               }

           }
       }
    }

    uint8_t *ShadingPipeline::getResult() {
       return image;
   }

    void ShadingPipeline::clearBuffer() {
        // clear buffer everytime when call shading pipeline
        memset(image,0,sizeof(uint8_t)*width*height*3);
        // DO NOT use memset to initialize except when setting value to 0 or -1 (巨坑。。。
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                zBuffer[i*width + j] = 2;
            }
        }
    }

}