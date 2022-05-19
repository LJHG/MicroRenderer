//
// Created by lm on 2022/5/19.
//

#include "CommonUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace MicroRenderer{
    Image CommonUtils::loadImage(std::string url) {
        int width,height,channel;
        uint8_t* rgb_image = stbi_load(url.c_str(), &width, &height, &channel, 3);
        Image image(rgb_image,width,height,channel);
        return image;
    }
}
