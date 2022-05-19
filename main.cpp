#include <iostream>
#include "WindowApp.h"
#include "CommonUtils.h"
using namespace  std;

const int WIDTH = 3840, HEIGHT = 2160; // SDL窗口的宽和高
int main() {
    MicroRenderer::WindowApp app(WIDTH,HEIGHT,"first window");
    while(!app.shouldWindowClose()){
        //处理事件
        app.processEvent();
        MicroRenderer::Image image = MicroRenderer::CommonUtils::loadImage("../assets/1.png");
        app.updateCanvas(image.pixels,image.width,image.height, image.channel);
    }

    return 0;
}
