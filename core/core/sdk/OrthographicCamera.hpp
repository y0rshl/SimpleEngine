//
// Created by paul on 18/08/16.
//

#ifndef SIMPLEENGINE_ORTHOGRAPHICCAMERA_H
#define SIMPLEENGINE_ORTHOGRAPHICCAMERA_H

#include "CameraComponent.hpp"

class OrthographicCamera : CameraComponent {
public:
    OrthographicCamera(float with, float height, float near, float far);
    Matrix4x4* getProjectionMatrix();

    void setWidth(float width);
    void setHeight(float height);
    void setNear(float near);
    void setFar(float far);

private:
    float width;
    float height;
    float near;
    float far;
};

#endif //SIMPLEENGINE_ORTHOGRAPHICCAMERA_H
