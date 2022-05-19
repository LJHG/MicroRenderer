//
// Created by lm on 2022/5/19.
//
//
#ifndef MICRORENDERER_COMMONUTILS_H
#define MICRORENDERER_COMMONUTILS_H

#include <iostream>
#include <string>




namespace MicroRenderer{

    struct Image{
        uint8_t* pixels;
        int width;
        int height;
        int channel;
        Image(uint8_t* _pixels, int _width, int _height, int _channel){
            pixels = _pixels;
            width = _width;
            height = _height;
            channel = _channel;
        }
    };

    class CommonUtils {

        /**
         * return an image array by a url
         * @param url
         * @return
         */
    public:
        static Image loadImage(std::string url);
    };
}




#endif //MICRORENDERER_COMMONUTILS_H
