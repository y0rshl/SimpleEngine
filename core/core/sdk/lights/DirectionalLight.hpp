//
// Created by paul on 06/09/16.
//

#ifndef SIMPLEENGINE_DIRECTIONALLIGHT_HPP
#define SIMPLEENGINE_DIRECTIONALLIGHT_HPP

#include "LightComponent.hpp"

class DirectionalLight:public LightComponent {
public:
    void update(double dt);
};

#endif //SIMPLEENGINE_DIRECTIONALLIGHT_HPP
