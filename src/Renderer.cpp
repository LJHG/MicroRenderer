//
// Created by lm on 2022/5/20.
//
#include "Renderer.h"

namespace MicroRenderer{
    void Renderer::setViewMatrix(const glm::mat4 &v) {
        if(shadingPipeline->shader == nullptr){
            std::cout<<"未定义shader"<<std::endl;
            return;
        }
        viewMatrix = v;
        shadingPipeline->shader->setViewMatrix(v);
    }

    void Renderer::setProjectionMatrix(const glm::mat4 &p) {
        if(shadingPipeline->shader == nullptr){
            std::cout<<"未定义shader"<<std::endl;
            return;
        }
        projectionMatrix = p;
        shadingPipeline->shader->setProjectionMatrix(p);
    }

    void Renderer::initShadingPipeline(int shadingMode) {
        Shader* shader = nullptr;
        if(shadingMode == SIMPLE_SHADER){
            shader = new SimpleShader();
        }
        else if(shadingMode == THREE_D_SHADER){
            shader = new ThreeDShader(modelMatrix,viewMatrix,projectionMatrix);
        }
        else if(shadingMode == GOURAUD_SHADER){
            shader = new GouraudShader(modelMatrix,viewMatrix,projectionMatrix);
        }
        else if(shadingMode == PHONG_SHADER){
            shader = new PhongShader(modelMatrix,viewMatrix,projectionMatrix);
        }
        else{
            //do nothing
        }
        shadingPipeline = new ShadingPipeline(width,height,shader);
    }

    Renderer::Renderer(int _width, int _height) {
        width = _width;
        height = _height;
        modelMatrix = glm::mat4(1.0f);
        viewMatrix = glm::mat4(1.0f);
        projectionMatrix = glm::mat4(1.0f);
    }

    void Renderer::render(Camera& camera) {
        if(meshes.empty()){
            std::cout<<"nothing to draw"<<std::endl;
        }
        shadingPipeline->clearBuffer();
        //set view matrix and projection matrix according to camera
        shadingPipeline->shader->setViewMatrix(MicroRenderer::MathUtils::calViewMatrix(camera.cameraPos,
                                                                                       camera.target,
                                                                                       camera.worldUp));
        shadingPipeline->shader->setProjectionMatrix(MicroRenderer::MathUtils::calPerspectiveProjectionMatrix(camera.fov,
                                                                                                              camera.aspectRatio,
                                                                                                                      camera.zNear,camera.zFar));
        shadingPipeline->shader->setEyePos(camera.cameraPos);

        //draw mesh
        for(Mesh m : meshes){
            // draw mesh one by one
            shadingPipeline->shader->setMaterial(m.getMaterial());
            shadingPipeline->shader->setTexture(m.getTextureUrl());
            shadingPipeline->shader->setModelMatrix(m.getModelMatrix());
            shadingPipeline->shade(m.getVertices(),m.getIndices(),FILL);
        }
    }

    void Renderer::setMeshes(const std::vector<Mesh> &_meshes) {
        meshes = _meshes;
    }

    uint8_t *Renderer::getPixelBuffer() {
        pixelBuffer = shadingPipeline->getResult();
        return pixelBuffer;
    }

    void Renderer::addDirectionLight(DirectionLight* light) {
        shadingPipeline->shader->addDirectionLight(light);
    }

    void Renderer::addPointLight(PointLight* light) {
        shadingPipeline->shader->addPointLight(light);
    }

}

