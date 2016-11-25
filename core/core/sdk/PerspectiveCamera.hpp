//
// Created by Andrea Lata on 11/25/16.
//

#ifndef SIMPLEENGINE_PERSPECTIVECAMERA_HPP
#define SIMPLEENGINE_PERSPECTIVECAMERA_HPP


#include "Camera.hpp"

class PerspectiveCamera : public Camera{

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

    //Metodo que devuelve la matriz de proyeccion de la camara
    Matrix4x4* getProjectionMatrix();
};


#endif //SIMPLEENGINE_PERSPECTIVECAMERA_HPP
