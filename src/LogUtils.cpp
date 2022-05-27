//
// Created by lm on 2022/5/25.
//

#include "LogUtils.h"

void MicroRenderer::LogUtils::log(glm::mat4& matrix) {
    //print by col
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<matrix[j][i]<<" ";
        }
        std::cout<<std::endl;
    }
}

void MicroRenderer::LogUtils::log(glm::vec3 &vector) {
    for(int i=0;i<3;i++){
        std::cout<<vector[i]<<" ";
    }
    std::cout<<std::endl;
}

void MicroRenderer::LogUtils::log(glm::vec4 &vector) {
    for(int i=0;i<4;i++){
        std::cout<<vector[i]<<" ";
    }
    std::cout<<std::endl;
}
