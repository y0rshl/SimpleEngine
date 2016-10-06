//
// Created by Andrea Lata on 9/8/16.
//

#ifndef SIMPLEENGINE_DIRECTIONALLIGHT_HPP
#define SIMPLEENGINE_DIRECTIONALLIGHT_HPP

#include "Light.hpp"

class DirectionalLight : public Light {

protected:
    Vec4 vec4 = Vec4(new float[4]{0,0,1,0});

public:
    DirectionalLight();
    Vec4 getDirLight();

    DirectionalLight(float width, float height, float far, float near);

    //Metodo que devuelve la matriz de view
    Matrix4x4* getProjectionMatrix();

private:
    float width;
    float height;
    float far;
    float near;

};


#endif //SIMPLEENGINE_DIRECTIONALLIGHT_HPP
