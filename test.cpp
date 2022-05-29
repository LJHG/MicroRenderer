//
// Created by lm on 2022/5/25.
//

#include <iostream>
#include <vector>
#include "LogUtils.h"
#include "glm/glm.hpp"
#include "CommonUtils.h"
#include "Structure.h"
using namespace std;

int main(){
    cout<<"hello world"<<endl;
    std::vector<MicroRenderer::Mesh> meshes = MicroRenderer::CommonUtils::loadObjModel("../assets/monkey_head/monkey_head.obj");
    MicroRenderer::Mesh mesh = meshes[0];
    std::cout<<mesh.getIndices().size()<<std::endl;
    std::cout<<mesh.getVertices().size()<<std::endl;
    return 0;
}