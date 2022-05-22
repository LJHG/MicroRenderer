//
// Created by lm on 2022/5/20.
//

#ifndef MICRORENDERER_RENDERER_H
#define MICRORENDERER_RENDERER_H

#include "glm/glm.hpp"

namespace MicroRenderer{
    class Renderer{
    public:

        void setModelMatrix(const glm::vec4& m);
        void setViewMatrix(const glm::vec4& v);
        void setProjectionMatrix(const glm::vec4& p);



    private:
        glm::vec4 model;
        glm::vec4 view;
        glm::vec4 projection;
    };

}

#endif //MICRORENDERER_RENDERER_H
