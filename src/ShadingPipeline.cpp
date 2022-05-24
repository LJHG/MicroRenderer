//
// Created by lm on 2022/5/22.
//

#include "ShadingPipeline.h"

namespace MicroRenderer{
   ShadingPipeline::ShadingPipeline(int _width, int _height, std::vector<VertexData> _vertices, std::vector<unsigned int> _indices) {
       width = _width;
       height = _height;
       vertices = _vertices;
       indices = _indices;
       image = (uint8_t*) malloc(sizeof(uint8_t)*width*height*3);
       imageSwap = (uint8_t*) malloc(sizeof(uint8_t)*width*height*3);
       //initialize buffer (avoid sparkle in the beginning)
       memset(image,0,sizeof(uint8_t)*width*height*3);
       memset(imageSwap,0,sizeof(uint8_t)*width*height*3);
       viewPortMatrix = MathUtils::calViewPortMatrix(0,0,width,height);
   }

    void ShadingPipeline::shade(int shadingMode, int rasterizingMode) {
        //according to indices, every 3 indices organize as a triangle, len(indices) could be greater than len(_vertices)
        if(shadingMode == SIMPLE_SHADER){
            shader = new SimpleShader();
        }
        VertexData v1,v2,v3;
        VertexOutData v1o,v2o,v3o;
        for(int i=0;i<indices.size()/3;i++){
            v1 = vertices[indices[i*3+0]];
            v2 = vertices[indices[i*3+1]];
            v3 = vertices[indices[i*3+2]];
            //vertex shader
            v1o = shader->vertexShader(v1);
            v2o = shader->vertexShader(v2);
            v3o = shader->vertexShader(v3);

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

            // double buffer
            swapBuffer();
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
            imageSwap[index +0] = static_cast<int>(color[0]);
            imageSwap[index +1] = static_cast<int>(color[1]);
            imageSwap[index +2] = static_cast<int>(color[2]);

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

       // get bounding box of the triangle
       int left = static_cast<int>(std::min(std::min(x1,x2),x3));
       int bottom = static_cast<int>(std::min(std::min(y1,y2),y3));
       int right = static_cast<int>(std::max(std::max(x1,x2),x3)) + 1; //ceil
       int top = static_cast<int>(std::max(std::max(y1,y2),y3)) + 1; //ceil

       for(int x = left;x<=right;x++){
           for(int y=bottom;y<=top;y++){
               if(MathUtils::insideTriangle(static_cast<float>(x),static_cast<float>(y),x1,y1,x2,y2,x3,y3)){
                   VertexOutData tmp = MathUtils::barycentricLerp(x,y,v1,v2,v3);
                   //fragment shader
                   glm::vec4 color = shader->fragmentShader(tmp);
                   int index = (y*width+x)*3;
                   imageSwap[index +0] = static_cast<int>(color[0]);
                   imageSwap[index +1] = static_cast<int>(color[1]);
                   imageSwap[index +2] = static_cast<int>(color[2]);
               }
           }
       }
    }

    uint8_t *ShadingPipeline::getResult() {
       return image;
   }

    void ShadingPipeline::swapBuffer() {
       // imageSwap -> image
       // don't know the use of double buffer for now... and maybe I write it wrong...
        uint8_t* tmp;
        image = imageSwap;
    }
}