//
// Created by lm on 2022/5/26.
//

#ifndef MICRORENDERER_CAMERA_H
#define MICRORENDERER_CAMERA_H

#include "glm/glm.hpp"

namespace MicroRenderer{
    class Camera {
    public:
        Camera(float _width, float _height);
        glm::vec3 cameraPos; // camera position
        glm::vec3 target; // camera focus position, target =  cameraPos + cameraFront
        glm::vec3 worldUp; // (0,1,0)
        float fov;
        float aspectRatio;
        float zNear;
        float zFar;
        float width;
        float height;
        float cameraMoveSpeed;
        float cameraTurnSpeed;
        glm::vec3 cameraFront; // camera direction
    };
}




#endif //MICRORENDERER_CAMERA_H
