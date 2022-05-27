//
// Created by lm on 2022/5/26.
//

#include "Camera.h"

namespace MicroRenderer{
    Camera::Camera(float _width,float _height) {
        width = _width;
        height = _height;
        fov = 600.0f;
        aspectRatio = width/height;
        zNear = 0.1f;
        zFar = 100.0f;
        cameraPos = glm::vec3(0,0,0);
        cameraFront = glm::vec3(0,0,1);
        target = cameraPos + cameraFront;
        worldUp = glm::vec3 (0,1,0);
        cameraMoveSpeed = 0.1f;
        cameraTurnSpeed = 0.1f;
    }
}


