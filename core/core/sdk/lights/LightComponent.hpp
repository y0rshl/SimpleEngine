//
// Created by paul on 06/09/16.
//

#ifndef SIMPLEENGINE_LIGHTCOMPONENT_HPP
#define SIMPLEENGINE_LIGHTCOMPONENT_HPP

#include "Component.hpp"

class LightComponent:public Component {
public:
    bool enabled;
    virtual void update(double dt) = 0;
};

#endif //SIMPLEENGINE_LIGHTCOMPONENT_HPP
