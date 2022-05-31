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
//    cout<<"hello world"<<endl;
//    std::vector<MicroRenderer::Mesh> meshes = MicroRenderer::CommonUtils::loadObjModel("../assets/monkey_head/monkey_head.obj");
//    MicroRenderer::Mesh mesh = meshes[0];
//    std::cout<<mesh.getIndices().size()<<std::endl;
//    std::cout<<mesh.getVertices().size()<<std::endl;
    MicroRenderer::Image image =MicroRenderer::CommonUtils::loadImage("../assets/test.png");
    std::cout<<image.width<<" "<<image.height<<std::endl;
    int idx1 = 0; //左上角
    std::cout<<(int)image.pixels[idx1+0]<<" "<<(int)image.pixels[idx1+1]<<" "<<(int)image.pixels[idx1+2]<<std::endl;
    int idx2 = (0*image.width + image.width -1)*3; //右上角
    std::cout<<(int)image.pixels[idx2+0]<<" "<<(int)image.pixels[idx2+1]<<" "<<(int)image.pixels[idx2+2]<<std::endl;
    int idx3 = ((image.height-1)*image.width)*3; //左下角
    std::cout<<(int)image.pixels[idx3+0]<<" "<<(int)image.pixels[idx3+1]<<" "<<(int)image.pixels[idx3+2]<<std::endl;
    int idx4 = (image.height*image.width)*3-3; //右下角
    std::cout<<(int)image.pixels[idx4+0]<<" "<<(int)image.pixels[idx4+1]<<" "<<(int)image.pixels[idx4+2]<<std::endl;
    return 0;
}