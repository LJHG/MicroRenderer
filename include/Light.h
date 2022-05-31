//
// Created by lm on 2022/5/29.
//

#ifndef MICRORENDERER_LIGHT_H
#define MICRORENDERER_LIGHT_H
#include "glm/glm.hpp"
#include <string>

class Light{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

};

class DirectionLight : public Light{
public:
    DirectionLight(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction);
    glm::vec3 direction;
};

class PointLight : public Light{
public:
    PointLight(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _position);
    void setLightPos(glm::vec3 _position);
    glm::vec3 position;
};

#endif //MICRORENDERER_LIGHT_H
