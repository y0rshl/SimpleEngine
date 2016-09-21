//
// Created by paul on 18/08/16.
//

#ifndef SIMPLEENGINE_CAMERACOMPONENT_H
#define SIMPLEENGINE_CAMERACOMPONENT_H

#include "Component.hpp"
#include "Matrix4x4.hpp"

class CameraComponent:public Component {
public:
    bool enabled;
    void update(double dt);
    Matrix4x4* getViewMatrix();
    virtual Matrix4x4* getProjectionMatrix() = 0;
    float* getPosition();
};

#endif //SIMPLEENGINE_CAMERACOMPONENT_H


