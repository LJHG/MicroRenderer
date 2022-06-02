//
// Created by lm on 2022/5/19.
//
//
#ifndef MICRORENDERER_COMMONUTILS_H
#define MICRORENDERER_COMMONUTILS_H

#include <iostream>
#include <string>
#include "Structure.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace MicroRenderer{

    struct Image{
        uint8_t* pixels;
        int width;
        int height;
        int channel;
        Image(){
            pixels = nullptr;
            width = 0;
            height = 0;
            channel = 0;
        }
        Image(uint8_t* _pixels, int _width, int _height, int _channel){
            pixels = _pixels;
            width = _width;
            height = _height;
            channel = _channel;
        }
    };

    class CommonUtils {


    public:
        /**
         * return an image array by an url
         * @param url
         * @return
         */
        static Image loadImage(std::string url);
        /**
         * return a vector of mesh by an url
         * 因为从一个obj文件里可能会读出多个mesh，所以还不能把这个函数当成Mesh这个类的成员函数，只好拿出来了。。。
         * @param url
         * @return
         */
        static std::vector<Mesh> loadObjModel(std::string filepath);

    };
}









#endif //MICRORENDERER_COMMONUTILS_H
