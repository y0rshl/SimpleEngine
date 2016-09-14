//
// Created by paul on 06/09/16.
//

#ifndef SIMPLEENGINE_POINTLIGHT_HPP
#define SIMPLEENGINE_POINTLIGHT_HPP

#include "LightComponent.hpp"
#include <math.h>

class PointLight:public LightComponent {
public:
    PointLight(weak_ptr<SceneObject> _owner);
    void update(double dt);
    float* getPosition();
};


#endif //SIMPLEENGINE_POINTLIGHT_HPP
