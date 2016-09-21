//
// Created by Andrea Lata on 9/21/16.
//

#ifndef SIMPLEENGINE_POINTLIGHT_HPP
#define SIMPLEENGINE_POINTLIGHT_HPP


#include "Light.hpp"

class PointLight : public Light {

public:
    PointLight(Vec4 vec);

    Vec4 getPosition();

private:
    Vec4 vec = 0;
};


#endif //SIMPLEENGINE_POINTLIGHT_HPP
