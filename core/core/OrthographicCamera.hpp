//
// Created by Andrea Lata on 11/25/16.
//

#ifndef SIMPLEENGINE_ORTHOGRAPHICCAMERA_HPP
#define SIMPLEENGINE_ORTHOGRAPHICCAMERA_HPP

#include <core/core/sdk/Camera.hpp>

class OrthographicCamera : public Camera {

private:
    float width;
    float height;
    float far;
    float near;

public:
    OrthographicCamera(float width, float height, float near, float far);

    void setWidth(float width);

    void setHeight(float height);

    void setFar(float far);

    void setNear(float near);

    //Metodo que devuelve la matriz de proyeccion de la camara
    Matrix4x4* getProjectionMatrix();
};


#endif //SIMPLEENGINE_ORTHOGRAPHICCAMERA_HPP
