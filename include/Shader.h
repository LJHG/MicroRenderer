//
// Created by lm on 2022/5/22.
//

#ifndef MICRORENDERER_SHADER_H
#define MICRORENDERER_SHADER_H

#include "Structure.h"

namespace MicroRenderer{
    class Shader {
    public:
        virtual VertexOutData vertexShader(VertexData& v)  {VertexOutData _v; return _v;}; //meaningless implementation
        virtual glm::vec4 fragmentShader(VertexOutData& v) {glm::vec4 r; return r;}; //meaningless implementation
        void setModelMatrix(glm::mat4 matrix);
        void setViewMatrix(glm::mat4 matrix);
        void setProjectionMatrix(glm::mat4 matrix);
    private:
        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    };

    class SimpleShader: public Shader{
    public:
        VertexOutData vertexShader(VertexData &v) override;
        glm::vec4 fragmentShader(VertexOutData &v) override;
    };
}



#endif //MICRORENDERER_SHADER_H
