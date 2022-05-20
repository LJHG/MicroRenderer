//
// Created by lm on 2022/5/20.
//

#include "MathUtils.h"


namespace MicroRenderer{

    glm::mat4 MathUtils::calViewMatrix(glm::vec3 cameraPos, glm::vec3 target, glm::vec3 worldUp){
        //copy from https://github.com/ZeusYang/TinySoftRenderer/blob/master/src/TRMathUtils.cpp
        glm::mat4 vMat;
        glm::vec3 zAxis = glm::normalize(cameraPos - target);
        glm::vec3 xAxis = glm::normalize(glm::cross(worldUp, zAxis));
        glm::vec3 yAxis = glm::normalize(glm::cross(zAxis, xAxis));

        vMat[0][0] = xAxis.x; vMat[0][1] = yAxis.x; vMat[0][2] = zAxis.x; vMat[0][3] = 0.0f;
        vMat[1][0] = xAxis.y; vMat[1][1] = yAxis.y; vMat[1][2] = zAxis.y; vMat[1][3] = 0.0f;
        vMat[2][0] = xAxis.z; vMat[2][1] = yAxis.z; vMat[2][2] = zAxis.z; vMat[2][3] = 0.0f;
        vMat[3][0] = -glm::dot(xAxis, cameraPos);
        vMat[3][1] = -glm::dot(yAxis, cameraPos);
        vMat[3][2] = -glm::dot(zAxis, cameraPos);
        vMat[3][3] = 1.0f;

        return vMat;
    }

    glm::mat4 MathUtils::calOrthoProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar) {
        float n = zNear;
        float f = zFar;
        float t = -tan( (fov/360)*PI ) * abs(n);
        float b = t * (-1);
        float r = aspectRatio * t;
        float l = r * (-1);

        //  matrix for orthographic
        glm::mat4 orthoScale = glm::mat4(1.0f);
        glm::mat4 orthoTrans = glm::mat4(1.0f);
        orthoScale[0][0] = 2/(r-l);
        orthoScale[1][1] = 2/(t-b);
        orthoScale[2][2] = 2/(n-f);

        orthoTrans[0][3] = (-1) * (r+l)/2;
        orthoTrans[1][3] = (-1) * (t+b)/2;
        orthoTrans[2][3] = (-1) * (n+f)/2;

        glm::mat4 orthoProjectionMatrix = orthoScale * orthoTrans;

        return orthoProjectionMatrix;
    }

    glm::mat4 MathUtils::calPerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar){
        float n = zNear;
        float f = zFar;
        float t = -tan( (fov/360)*PI ) * abs(n);
        float b = t * (-1);
        float r = aspectRatio * t;
        float l = r * (-1);

        //  matrix for orthographic
        glm::mat4 orthoProjectionMatrix = calOrthoProjectionMatrix(fov,aspectRatio,zNear,zFar);

        // perspective -> ortho matrix
        glm::mat4 pers2Ortho = glm::mat4(0);
        pers2Ortho[0][0] = n;
        pers2Ortho[1][1] = n;
        pers2Ortho[3][2] = 1;
        pers2Ortho[2][2] = n+f;
        pers2Ortho[2][3] = (-1)*n*f;

        // cal projection matrix
        glm::mat4 perspectiveProjectionMatrix = orthoProjectionMatrix * pers2Ortho;
        return perspectiveProjectionMatrix;
    }

}
