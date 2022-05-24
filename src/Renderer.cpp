//
// Created by lm on 2022/5/20.
//
#include "Renderer.h"

namespace MicroRenderer{
    void Renderer::setModelMatrix(const glm::mat4 &m) {
        modelMatrix = m;
    }

    void Renderer::setViewMatrix(const glm::mat4 &v) {
        viewMatrix = v;
    }

    void Renderer::setProjectionMatrix(const glm::mat4 &p) {
        projectionMatrix = p;
    }

    void Renderer::setShader(int shadingMode) {
        if(shadingMode == SIMPLE_SHADER){
            shader = new SimpleShader();
        }
        else if(shadingMode == THREE_D_SHADER){
            shader = new ThreeDShader(modelMatrix,viewMatrix,projectionMatrix);
        }
    }

    void Renderer::initShadingPipeline() {
        if(shader == nullptr){
            std::cout<<"should set a shader first"<<std::endl;
            return;
        }
        shadingPipeline = new ShadingPipeline(width,height,shader);
    }

    Renderer::Renderer(int _width, int _height) {
        width = _width;
        height = _height;
    }

    void Renderer::render() {
        if(meshes.empty()){
            std::cout<<"nothing to draw"<<std::endl;
        }
        for(Mesh m : meshes){
            // draw mesh one by one
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
}

