//
// Created by lm on 2022/5/20.
//

#ifndef MICRORENDERER_MATHUTILS_H
#define MICRORENDERER_MATHUTILS_H

#include "glm/glm.hpp"

#define PI 3.1415926

namespace MicroRenderer{
    /**
     * math calculation class, provide functions such model, view, projection matrix calculation and so on...
     */
    class MathUtils {
    public:
        static glm::mat4 calViewMatrix(glm::vec3 cameraPos, glm::vec3 target, glm::vec3 worldUp);
        static glm::mat4 calOrthoProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
        static glm::mat4 calPerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
    };
}



#endif //MICRORENDERER_MATHUTILS_H
