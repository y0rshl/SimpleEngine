//
// Created by Andrea Lata on 9/8/16.
//

#ifndef SIMPLEENGINE_LIGHT_HPP
#define SIMPLEENGINE_LIGHT_HPP

#include "Component.hpp"
#include "Matrix4x4.hpp"
#include "Transform.hpp"

class Light : public Component {

public:

    Light();
    void update(double dt);

    Matrix4x4* getViewMatrix();

};


#endif //SIMPLEENGINE_LIGHT_HPP
