//
// Created by lm on 2022/5/25.
//

#include <iostream>
#include "LogUtils.h"
#include "glm/glm.hpp"
using namespace std;

int main(){
    cout<<"hello world"<<endl;
    glm::mat4 matrix(1.0f);
    matrix[0][2] = 2.0f;
    MicroRenderer::LogUtils::print(matrix);
    return 0;
}