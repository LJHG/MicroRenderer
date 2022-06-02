//
// Created by lm on 2022/5/20.
//

#include "MathUtils.h"


namespace MicroRenderer{

    /**** copy view matrix and projection matrix ****/
    glm::mat4 MathUtils::calViewMatrix(glm::vec3 cameraPos, glm::vec3 target, glm::vec3 worldUp){
        //copy from https://github.com/ZeusYang/TinySoftRenderer/blob/master/src/TRMathUtils.cpp
//        std::cout<<"using copy view matrix"<<std::endl;
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

    glm::mat4 MathUtils::calPerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar)
    {
        //copy from https://github.com/ZeusYang/TinySoftRenderer/blob/master/src/TRMathUtils.cpp
        //Setup perspective matrix (camera space -> homogeneous space)
        //std::cout<<"using copy projection matrix"<<std::endl;
        glm::mat4 pMat = glm::mat4(1.0f);

        float rFovy = fov * 3.14159265358979323846 / 180;
        const float tanHalfFovy = std::tan(rFovy * 0.5f);
        float f_n = zFar - zNear;
        pMat[0][0] = 1.0f / (aspectRatio*tanHalfFovy); pMat[0][1] = 0.0f;				pMat[0][2] = 0.0f;					pMat[0][3] = 0.0f;
        pMat[1][0] = 0.0f;						  pMat[1][1] = 1.0f / tanHalfFovy;  pMat[1][2] = 0.0f;					pMat[1][3] = 0.0f;
        pMat[2][0] = 0.0f;						  pMat[2][1] = 0.0f;			    pMat[2][2] = -(zFar + zNear) / f_n;	pMat[2][3] = -1.0f;
        pMat[3][0] = 0.0f;						  pMat[3][1] = 0.0f;				pMat[3][2] = -2.0f*zNear*zFar / f_n;	pMat[3][3] = 0.0f;
        return pMat;
    }

    /**** self implement view matrix and projection matrix ****/

    //TODO: 自己实现的计算view matrix的函数也不太对。。。先使用copy的版本

//    glm::mat4 MathUtils::calViewMatrix(glm::vec3 cameraPos, glm::vec3 target, glm::vec3 worldUp){
//        //self implementing -> according to games101 p3
//        //std::cout<<"using self implement view matrix"<<std::endl;
//        glm::mat4 vMat;
//
//        glm::mat4 rotation(1.0f);
//        glm::mat4 translation(1.0f);
//
//        target = glm::normalize(target-cameraPos); //the input target is a position, we need to transform it to a vector
//
//        glm::vec3 g_cross_t = glm::cross(target,worldUp);
//
//        // rotation matrix
//        //first row
//        rotation[0][0] = g_cross_t[0]; rotation[1][0] = g_cross_t[1]; rotation[2][0] = g_cross_t[2];
//        //second row
//        rotation[0][1] = worldUp[0]; rotation[1][1] = worldUp[1]; rotation[2][1] = worldUp[2];
//        //third row
//        rotation[0][2] = -target[0]; rotation[1][2] = -target[1]; rotation[2][2] = -target[2];
//
//        //translation matrix
//        // last column
//        translation[3][0] = -cameraPos[0]; translation[3][1] = -cameraPos[1]; translation[3][2] = -cameraPos[2];
//        vMat = rotation * translation;
//
//        return vMat;
//    }


    //TODO: 透视投影后的z分量又有点不对。。。不在 [-1,1]内，目前先使用copy的透视投影计算。

//    glm::mat4 MathUtils::calPerspectiveProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar){
//        //copy from games101
//        //std::cout<<"using self implement projection matrix"<<std::endl;
//        float n = zNear;
//        float f = zFar;
//
//        //  matrix for orthographic
//        glm::mat4 orthoProjectionMatrix = calOrthoProjectionMatrix(fov,aspectRatio,zNear,zFar);
//
//        // perspective -> ortho matrix
//        glm::mat4 pers2Ortho = glm::mat4(0);
//        pers2Ortho[0][0] = n;
//        pers2Ortho[1][1] = n;
//        pers2Ortho[2][3] = 1;
//        pers2Ortho[2][2] = n+f;
//        pers2Ortho[3][2] = (-1)*n*f;
//
//        // cal projection matrix
//        glm::mat4 perspectiveProjectionMatrix = orthoProjectionMatrix * pers2Ortho;
//        return perspectiveProjectionMatrix;
//    }


    glm::mat4 MathUtils::calOrthoProjectionMatrix(float fov, float aspectRatio, float zNear, float zFar) {
        // copy from games101
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

        orthoTrans[3][0] = (-1) * (r+l)/2;
        orthoTrans[3][1] = (-1) * (t+b)/2;
        orthoTrans[3][2] = (-1) * (n+f)/2;

        glm::mat4 orthoProjectionMatrix = orthoScale * orthoTrans;

        return orthoProjectionMatrix;
    }



    glm::mat4 MathUtils::calViewPortMatrix(int left, int top, int width, int height) {
        // the matrix in glm in stored by column... , so matrix[x][y] access the element of x col ,y row
        glm::mat4 viewPortMatrix(1.0f);
        viewPortMatrix[0][0] = static_cast<float>(width)/2.0f;
        viewPortMatrix[3][0] = static_cast<float>(left) + static_cast<float>(width)/2.0f;
        viewPortMatrix[1][1] = static_cast<float>(height)/2.0f;
        viewPortMatrix[3][1] = static_cast<float>(top) + static_cast<float>(height)/2.0f;
        return viewPortMatrix;
    }

    VertexOutData MathUtils::lerp(VertexOutData from, VertexOutData to, float t) {
        // from -> t = 0  to -> t = 1
        // currently, interpolate for position, color and normal
        VertexOutData vResult;
        vResult.position = from.position  + (to.position - from.position) * t;
        vResult.normal = from.normal + (to.normal - from.normal) * t;
        vResult.color = from.color + (to.color - from.color) * t;

        return vResult;
    }

    VertexOutData MathUtils::barycentricLerp(int x, int y, VertexOutData v1, VertexOutData v2, VertexOutData v3) {
        auto[alpha, beta, gamma] = computeBarycentric2D(static_cast<float>(x+0.5f), static_cast<float>(y+0.5f), // need to add 0.5f to get the center coordinate of the pixel
                                                        v1.position[0],v1.position[1],
                                                        v2.position[0],v2.position[1],
                                                        v3.position[0],v3.position[1]);
        VertexOutData vResult;
        vResult.position = v1.position * alpha  + v2.position * beta +  v3.position*gamma;
        vResult.color = v1.color * alpha  + v2.color * beta +  v3.color*gamma;
        // TODO:关于三维空间的插值是否可以这样做的问题。。。。 目前先使用直接插值的方法
        vResult.worldPos = v1.worldPos * alpha  + v2.worldPos * beta +  v3.worldPos*gamma;
        vResult.normal = v1.normal * alpha  + v2.normal * beta + v3.normal*gamma;
        vResult.textureCoord = v1.textureCoord * alpha  + v2.textureCoord * beta + v3.textureCoord * gamma;
        return vResult;
    }

    bool MathUtils::insideTriangle(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3) {
        // 其实传进来的应该是，不过这里直接写成float了，在函数外直接强转
        // check if the point p(x, y) is inside the triangle
        x = x + 0.5f;
        y = y + 0.5f;

        float a1 = x1-x; float a2 = y1-y;
        float b1 = x2-x; float b2 = y2-y;
        float c1 = x3-x; float c2 = y3-y;

        float papb = crossProduct(a1,a2,b1,b2);
        float pbpc = crossProduct(b1,b2,c1,c2);
        float pcpa = crossProduct(c1,c2,a1,a2);

        if( (papb > 0 && pbpc > 0 && pcpa >0)  || (papb < 0 && pbpc < 0 && pcpa < 0) )
            return true;
        return false;
    }

    float MathUtils::crossProduct(float a1, float a2, float b1, float b2) {
        // return product of vector (a1,a2) and (b1,b2)
        return a1*b2 - a2*b1;
    }

    std::tuple<float, float, float>
    MathUtils::computeBarycentric2D(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3) {
        float c1 = (x*(y2 - y3) + (x3 - x2)*y + x2*y3 - x3*y2) / (x1*(y2 - y3) + (x3 - x2)*y1 + x2*y3 - x3*y2);
        float c2 = (x*(y3 - y1) + (x1 - x3)*y + x3*y1 - x1*y3) / (x2*(y3 - y1) + (x1 - x3)*y2 + x3*y1 - x1*y3);
        float c3 = (x*(y1 - y2) + (x2 - x1)*y + x1*y2 - x2*y1) / (x3*(y1 - y2) + (x2 - x1)*y3 + x1*y2 - x2*y1);
        return {c1,c2,c3};
    }

    glm::mat4 MathUtils::rotationByX(const glm::mat4 matrix, const double angle) {
        glm::mat4 resultMatrix(1.0f);
        glm::mat4 rotationMatrix(1.0f);
        float degree = (angle*PI)/180.0f;
        rotationMatrix[1][1] = cos(degree); rotationMatrix[1][2] = sin(degree);
        rotationMatrix[2][1] = -sin(degree);rotationMatrix[2][2] = cos(degree);
        return rotationMatrix * matrix;
    }

    float MathUtils::calPoint2PointSquareDistance(glm::vec3 pos1, glm::vec3 pos2) {
        return (pos1[0]-pos2[0])*(pos1[0]-pos2[0]) + (pos1[1]-pos2[1])*(pos1[1]-pos2[1]) + (pos1[2]-pos2[2])*(pos1[2]-pos2[2]);
    }


}
