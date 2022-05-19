//
// Created by lm on 2022/5/17.
//

#include "WindowApp.h"

namespace MicroRenderer{
    WindowApp::WindowApp(int width, int height, std::string title) {
        quit = false;

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // 初始化SDL
            std::cout << "SDL could not initialized with error: " << SDL_GetError() << std::endl;
        }
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI); // 创建SDL窗口
        if (NULL == window) {
            std::cout << "SDL could not create window with error: " << SDL_GetError() << std::endl;
        }
        windowSurface = SDL_GetWindowSurface(window);
    }


    void WindowApp::updateCanvas(uint8_t* pixels, int width, int height, int channel) {
        SDL_LockSurface(windowSurface);
        Uint32* surfacePixels = (Uint32*)windowSurface->pixels; //获取当前屏幕的像素指针
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                int index = i*width + j;
                Uint32 _color = SDL_MapRGB(
                        windowSurface->format,
                        pixels[index * channel + 0],
                        pixels[index * channel + 1],
                        pixels[index * channel + 2]);
                surfacePixels[index] = _color;
            }
        }
        SDL_UnlockSurface(windowSurface);
        SDL_UpdateWindowSurface(window);
    }

    void WindowApp::processEvent() {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if(event.button.button == SDL_BUTTON_LEFT){
                std::cout<<"left mouse clicked"<<std::endl;
            }
        }
    }

    bool WindowApp::shouldWindowClose() {
        return quit;
    }

    WindowApp::~WindowApp() {
//        delete windowSurface;
//        SDL_DestroyWindow(window); // 退出SDL窗体
//        window = nullptr;
        //maybe some bugs...
        SDL_Quit(); // SDL退出
    }

}
