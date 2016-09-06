//
// Created by paul on 06/09/16.
//

#ifndef SIMPLEENGINE_SPOTLIGHT_HPP
#define SIMPLEENGINE_SPOTLIGHT_HPP

#include "LightComponent.hpp"

class SpotLight:public LightComponent {
public:
    void update(double dt);
};

#endif //SIMPLEENGINE_SPOTLIGHT_HPP
