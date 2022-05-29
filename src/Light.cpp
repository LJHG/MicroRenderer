//
// Created by lm on 2022/5/29.
//

#include "Light.h"

DirectionLight::DirectionLight(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction) {
    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
    direction = _direction;
}
