//
// Created by lm on 2022/5/20.
//
#include "Renderer.h"

namespace MicroRenderer{
    void Renderer::setModelMatrix(const glm::vec4 &m) {
        model = m;
    }

    void Renderer::setViewMatrix(const glm::vec4 &v) {
        view = v;
    }

    void Renderer::setProjectionMatrix(const glm::vec4 &p) {
        projection = p;
    }
}

