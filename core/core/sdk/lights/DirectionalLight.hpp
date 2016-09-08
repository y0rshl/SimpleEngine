//
// Created by paul on 06/09/16.
//

#ifndef SIMPLEENGINE_DIRECTIONALLIGHT_HPP
#define SIMPLEENGINE_DIRECTIONALLIGHT_HPP

#include "LightComponent.hpp"
#include <math.h>

class DirectionalLight:public LightComponent {
public:
    DirectionalLight(weak_ptr<SceneObject> _owner);
    void update(double dt);
    float* getDirection();
};

#endif //SIMPLEENGINE_DIRECTIONALLIGHT_HPP
