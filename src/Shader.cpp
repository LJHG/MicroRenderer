//
// Created by lm on 2022/5/22.
//

#include "Shader.h"

namespace MicroRenderer{
    /**** Base Shader ****/
    void Shader::setModelMatrix(glm::mat4 matrix) {
        modelMatrix = matrix;
    }

    void Shader::setViewMatrix(glm::mat4 matrix) {
        viewMatrix = matrix;
    }

    void Shader::setProjectionMatrix(glm::mat4 matrix) {
        projectionMatrix = matrix;
    }

    /**** Simple Shader ****/

    // simple vertex shader just pass the value
    VertexOutData SimpleShader::vertexShader(VertexData &v) {
        VertexOutData vod;
        vod.position = glm::vec4(v.position,1.0f);
        vod.color= v.color;
        vod.normal = v.normal;
        return vod;
    }

    glm::vec4 SimpleShader::fragmentShader(VertexOutData &v) {
        glm::vec4 result;
        result = v.color;
        return result;
    }


    /**** Three D Shader ****/
    ThreeDShader::ThreeDShader(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix) {
        modelMatrix = _modelMatrix;
        viewMatrix = _viewMatrix;
        projectionMatrix = _projectionMatrix;
    }

    VertexOutData ThreeDShader::vertexShader(VertexData &v) {
        VertexOutData vod;
        vod.position = glm::vec4(v.position,1.0f);
        vod.position = projectionMatrix * viewMatrix * modelMatrix * vod.position; //mvp transformation
        vod.color= v.color;
        vod.normal = v.normal;
        return vod;
    }

    glm::vec4 ThreeDShader::fragmentShader(VertexOutData &v) {
        glm::vec4 result;
        result = v.color;
        return result;
    }
}