//
// Created by lm on 2022/5/17.
//

#ifndef MICRORENDERER_WINDOWAPP_H
#define MICRORENDERER_WINDOWAPP_H

#include <string>
#include "SDL2/SDL.h"
#include <iostream>


namespace MicroRenderer{
    class WindowApp {
    public:
        WindowApp(int width, int height, std::string title);
        virtual ~WindowApp();
        void updateCanvas(uint8_t* pixels,int width, int height,int channel);
        void processEvent();
        bool shouldWindowClose();

    private:
        SDL_Window* window;
        SDL_Surface* windowSurface;
        bool quit;
        SDL_Event event;
    };

}



#endif //MICRORENDERER_WINDOWAPP_H
