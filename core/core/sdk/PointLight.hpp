//
// Created by Andrea Lata on 9/21/16.
//

#ifndef SIMPLEENGINE_POINTLIGHT_HPP
#define SIMPLEENGINE_POINTLIGHT_HPP


#include "Light.hpp"

class PointLight : public Light {

public:
    PointLight();

    Vec4 getPosition(); //un punto

};


#endif //SIMPLEENGINE_POINTLIGHT_HPP
