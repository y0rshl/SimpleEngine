//
// Created by paul on 06/09/16.
//

#ifndef SIMPLEENGINE_POINTLIGHT_HPP
#define SIMPLEENGINE_POINTLIGHT_HPP

#include "LightComponent.hpp"

class PointLight:public LightComponent {
public:
    void update(double dt);
};


#endif //SIMPLEENGINE_POINTLIGHT_HPP
