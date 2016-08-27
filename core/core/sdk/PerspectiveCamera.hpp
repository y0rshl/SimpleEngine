//
// Created by Andrea Lata on 8/18/16.
//

#ifndef SIMPLEENGINE_PERSPECTIVECAMERA_HPP
#define SIMPLEENGINE_PERSPECTIVECAMERA_HPP

#include "Camera.h"

class PerspectiveCamera : public Camera {

private:
    float fovX;
    float fovY;
    float near;
    float far;

public:

    PerspectiveCamera(float fovX, float fovY, float near, float far);

    void setFovX(float fovX);

    void setFovY(float fovY);

    void setNear(float near);

    void setFar(float far);

    //Metodo que devuelve la matriz de view
    Matrix4x4* getProjectionMatrix();
};


#endif //SIMPLEENGINE_PERSPECTIVECAMERA_HPP
