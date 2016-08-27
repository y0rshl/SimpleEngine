//
// Created by paul on 18/08/16.
//

#ifndef SIMPLEENGINE_PERSPECTIVECAMERA_H
#define SIMPLEENGINE_PERSPECTIVECAMERA_H

#include "CameraComponent.hpp"

class PerspectiveCamera : public CameraComponent {

public:
    PerspectiveCamera(float fovX, float fovY, float near, float far);
    Matrix4x4* getProjectionMatrix();

    void setFovX(float fovX);
    void setFovY(float fovY);
    void setNear(float near);
    void setFar(float far);

private:
    float fovX;
    float fovY;
    float near;
    float far;
};

#endif //SIMPLEENGINE_PERSPECTIVECAMERA_H
