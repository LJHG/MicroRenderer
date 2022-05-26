//
// Created by lm on 2022/5/25.
//

#ifndef MICRORENDERER_LOGUTILS_H
#define MICRORENDERER_LOGUTILS_H

#include <glm/glm.hpp>
#include <iostream>

namespace MicroRenderer{
    class LogUtils {
    public:
        static void log(glm::mat4& matrix);
    };
}



#endif //MICRORENDERER_LOGUTILS_H
