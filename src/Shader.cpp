//
// Created by lm on 2022/5/22.
//

#include "Shader.h"
#include "MathUtils.h"

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
    void Shader::setMaterial(Material _material) {
        material = _material;
    }

    void Shader::setEyePos(glm::vec3 _eyePos) {
        eyePos = _eyePos;
    }

    void Shader::addDirectionLight(DirectionLight* light) {
        directionLights.push_back(light);
    }

    void Shader::addPointLight(PointLight* light) {
        pointLights.push_back(light);
    }

    void Shader::setTexture(std::string _textureUrl) {
        textureUrl = _textureUrl;
        texture = CommonUtils::loadImage(textureUrl);
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

    /**** Gouraud Shader****/
    GouraudShader::GouraudShader(glm::mat4 _modelMatrix,
                                 glm::mat4 _viewMatrix,
                                 glm::mat4 _projectionMatrix) {
        modelMatrix = _modelMatrix;
        viewMatrix = _viewMatrix;
        projectionMatrix = _projectionMatrix;
        //
        directionLights.clear();
        pointLights.clear();
        textureUrl = "none";
    }

    VertexOutData GouraudShader::vertexShader(VertexData &v) {
        VertexOutData vod;
        vod.position = glm::vec4(v.position,1.0f);
        vod.position = projectionMatrix * viewMatrix * modelMatrix * vod.position; //mvp transformation
        vod.normal = v.normal;

        // 计算着色
        glm::vec3 ka = material.ka;
        glm::vec3 kd = material.kd;
        if(textureUrl != "none"){
            int xIdx = v.textureCoord[0] * texture.width;
            int yIdx = (1-v.textureCoord[1]) * texture.height;
            int idx = (yIdx * texture.width + xIdx)*3;
            kd = glm::vec3(texture.pixels[idx+0]/255.0f,
                           texture.pixels[idx+1]/255.0f,
                           texture.pixels[idx+2]/255.0f);
        }
        glm::vec3 ks = material.ks;

        glm::vec3 color(0.0f,0.0f,0.0f);

        //directional lights
        for(const auto& light:directionLights){
            glm::vec3 lightDir = glm::normalize(-light->direction); // pos -> light
            glm::vec3 viewDir = glm::normalize(eyePos - v.position); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量
            glm::vec3 L_a = light->ambient * kd;
            glm::vec3 L_d = light->diffuse * kd * std::max(0.0f,glm::dot(v.normal,lightDir));
            glm::vec3 L_s = light->specular * ks * pow(std::max(0.0f,glm::dot(v.normal,half)),material.shininess);


            color += (L_a + L_d + L_s)*255.0f;
        }

        //point lights
        for(const auto& light:pointLights){
            glm::vec3 lightDir = glm::normalize(light->position - v.position); // pos -> light
            glm::vec3 viewDir = glm::normalize(eyePos - v.position); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量

            float distance = MathUtils::calPoint2PointSquareDistance(v.position,light->position);

            glm::vec3 L_d = light->diffuse * kd * std::max(0.0f,glm::dot(v.normal,lightDir));
            glm::vec3 L_s = light->specular * ks * pow(std::max(0.0f,glm::dot(v.normal,half)),material.shininess);


            color += (L_d/distance + L_s/distance)*255.0f;
        }


        color = glm::vec3(std::min(color[0],255.0f), std::min(color[1],255.0f),std::min(color[2],255.0f));

        vod.color = glm::vec4(color,1.0f);

        return vod;
    }

    glm::vec4 GouraudShader::fragmentShader(VertexOutData &v) {
        return v.color;
    }

    /**** Phong Shader****/
    PhongShader::PhongShader(glm::mat4 _modelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix) {
        modelMatrix = _modelMatrix;
        viewMatrix = _viewMatrix;
        projectionMatrix = _projectionMatrix;
        //
        directionLights.clear();
        pointLights.clear();
        textureUrl = "none";
    }

    VertexOutData PhongShader::vertexShader(VertexData &v) {
        VertexOutData vod;
        vod.position = glm::vec4(v.position,1.0f);
        vod.position = projectionMatrix * viewMatrix * modelMatrix * vod.position; //mvp transformation
        vod.worldPos = modelMatrix * glm::vec4(v.position,1.0f);  // vec3 = vec4...
        vod.normal = v.normal;
        vod.textureCoord = v.textureCoord;

        return vod;
    }

    glm::vec4 PhongShader::fragmentShader(VertexOutData &v) {
        // 计算着色
        glm::vec3 ka = material.ka;
        glm::vec3 kd = material.kd;
        if(textureUrl != "none"){
            int xIdx = v.textureCoord[0] * texture.width;
            int yIdx = (1-v.textureCoord[1]) * texture.height;
            int idx = (yIdx * texture.width + xIdx)*3;
            kd = glm::vec3(texture.pixels[idx+0]/255.0f,
                           texture.pixels[idx+1]/255.0f,
                           texture.pixels[idx+2]/255.0f);
        }
        glm::vec3 ks = material.ks;

        glm::vec3 color(0.0f,0.0f,0.0f);

        //directional lights
        for(const auto& light:directionLights){
            glm::vec3 lightDir = glm::normalize(-light->direction); // pos -> light
            glm::vec3 viewDir = glm::normalize(eyePos - v.worldPos); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量
            glm::vec3 L_a = light->ambient * kd;
            glm::vec3 L_d = light->diffuse * kd * std::max(0.0f,glm::dot(v.normal,lightDir));
            glm::vec3 L_s = light->specular * ks * pow(std::max(0.0f,glm::dot(v.normal,half)),material.shininess);


            color += (L_a + L_d + L_s)*255.0f;
        }

        //point lights
        for(const auto& light:pointLights){
            glm::vec3 lightDir = glm::normalize(light->position - v.worldPos); // pos -> light
            glm::vec3 viewDir = glm::normalize(eyePos - v.worldPos); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量

            float distance = MathUtils::calPoint2PointSquareDistance(v.worldPos,light->position);

            glm::vec3 L_d = light->diffuse * kd * std::max(0.0f,glm::dot(v.normal,lightDir));
            glm::vec3 L_s = light->specular * ks * pow(std::max(0.0f,glm::dot(v.normal,half)),material.shininess);


            color += (L_d/distance + L_s/distance)*255.0f;
        }


        color = glm::vec3(std::min(color[0],255.0f), std::min(color[1],255.0f),std::min(color[2],255.0f));



        return glm::vec4(color,1.0f);
    }


}