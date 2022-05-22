#include <iostream>
#include "WindowApp.h"
#include "CommonUtils.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "stb_image.h"
using namespace  std;

const int WIDTH = 640, HEIGHT = 480; // SDL窗口的宽和高
int main() {
    MicroRenderer::WindowApp app(WIDTH,HEIGHT,"first window");
    while(!app.shouldWindowClose()){
        //处理事件
        app.processEvent();
//        MicroRenderer::Image image = MicroRenderer::CommonUtils::loadImage("../assets/1.png");
        uint8_t pixels[WIDTH*HEIGHT*3];
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                int index = (i*WIDTH+j)*3;
                pixels[index+0] = 128;
                pixels[index+1] = 128;
                pixels[index+2] = 128;
            }
        }
        app.updateCanvas(pixels,WIDTH,HEIGHT, 3);
    }

    return 0;
}
