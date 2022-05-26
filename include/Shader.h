//
// Created by lm on 2022/5/22.
//

#ifndef MICRORENDERER_SHADER_H
#define MICRORENDERER_SHADER_H

#include "Structure.h"
#include <iostream>
#include "LogUtils.h"

namespace MicroRenderer{
    class Shader {
    public:
        Shader() = default;
        virtual VertexOutData vertexShader(VertexData& v)  {VertexOutData _v; return _v;}; //meaningless implementation
        virtual glm::vec4 fragmentShader(VertexOutData& v) {glm::vec4 r; return r;}; //meaningless implementation
        void setModelMatrix(glm::mat4 matrix);
        void setViewMatrix(glm::mat4 matrix);
        void setProjectionMatrix(glm::mat4 matrix);

    protected:
        glm::mat4 modelMatrix{};
        glm::mat4 viewMatrix{};
        glm::mat4 projectionMatrix{};
    };

    // simple shader, just pass data, didn't do anything
    class SimpleShader: public Shader{
    public:
        VertexOutData vertexShader(VertexData &v) override;
        glm::vec4 fragmentShader(VertexOutData &v) override;
    };

    // 3d shader, implement mvp transformation for vertex shader, fragment shader just pass color
    class ThreeDShader: public Shader{
    public:
        ThreeDShader(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix);
        VertexOutData vertexShader(VertexData &v) override;
        glm::vec4 fragmentShader(VertexOutData &v) override;
    };


}



#endif //MICRORENDERER_SHADER_H
