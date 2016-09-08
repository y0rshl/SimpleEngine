//
// Created by Andrea Lata on 9/8/16.
//

#ifndef SIMPLEENGINE_LIGHT_HPP
#define SIMPLEENGINE_LIGHT_HPP

#include "Component.hpp"
#include "Matrix4x4.hpp"

class Light : public Component {

protected:
    float vec4[4] = {0,0,1,0};

public:

    Light();
    void update(double dt);

    float* getDirLight();
};


#endif //SIMPLEENGINE_LIGHT_HPP
