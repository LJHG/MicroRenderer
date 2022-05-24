//
// Created by lm on 2022/5/20.
//

#ifndef MICRORENDERER_MATHUTILS_H
#define MICRORENDERER_MATHUTILS_H

#include "glm/glm.hpp"
#include "Structure.h"
#include <iostream>

#define PI 3.1415926

namespace MicroRenderer{
    /**
     * math calculation class, provide functions such as:
     * 1. model, view, projection matrix calculation and so on...
     * 2. interpolation related function
     * 3. judge if a pixel is inside a triangle ...
     */
    class MathUtils {
    public:
        static glm::mat4 calViewMatrix(glm::vec3 cameraPos, glm::vec3 target, glm::vec3 worldUp);
        static glm::mat4 calOrthoProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
        static glm::mat4 calPerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar);
        static glm::mat4 calViewPortMatrix(int left, int top, int width, int height);
        static VertexOutData lerp(VertexOutData from, VertexOutData to, float t); // interpolation for VertexOut data, for line drawing
        static VertexOutData barycentricLerp(int x, int y, VertexOutData v1, VertexOutData v2, VertexOutData v3); // interpolation for VertexOut data, for fill drawing
        static std::tuple<float, float, float> computeBarycentric2D(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3);
        static bool insideTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3);
        static float crossProduct(float a1, float a2, float b1, float b2);

    };
}



#endif //MICRORENDERER_MATHUTILS_H
