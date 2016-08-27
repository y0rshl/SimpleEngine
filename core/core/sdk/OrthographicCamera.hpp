//
// Created by Andrea Lata on 8/18/16.
//

#ifndef SIMPLEENGINE_ORTHOGRAPHICCAMERA_HPP
#define SIMPLEENGINE_ORTHOGRAPHICCAMERA_HPP

#include "Transform.hpp"
#include "Camera.h"

class OrthographicCamera : public Camera {

private:
    float width;
    float height;
    float far;
    float near;

public:

    OrthographicCamera(float width, float height, float far, float near);

    void setWidth(float width);

    void setHeight(float height);

    void setFar(float far);

    void setNear(float near);

    //Metodo que devuelve la matriz de view
    Matrix4x4* getProjectionMatrix();
};


#endif //SIMPLEENGINE_ORTHOGRAPHICCAMERA_HPP
