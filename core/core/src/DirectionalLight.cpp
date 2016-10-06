//
// Created by Andrea Lata on 9/8/16.
//

#include "DirectionalLight.hpp"
#include <core/core/sdk/SceneObject.hpp>

DirectionalLight::DirectionalLight() {
}

DirectionalLight::DirectionalLight (float width , float height , float far , float near) {
    this->width = width;
    this->height = height;
    this->far = far;
    this->near = near;
}

Vec4 DirectionalLight::getDirLight () {
    //Muliplico TRS * (0,0,1)
    shared_ptr<SceneObject> light;

    light = this->owner.lock();
    SceneObject *so = light.get();
    Matrix4x4 *trs = so->getPosition();

    return trs->multVec4(this->vec4); //con esta multiplicacion te quedas con el vector z (q es hacia donde apunta el objeto)
}

Matrix4x4 *DirectionalLight::getProjectionMatrix () {
    float r[16];

    r[0] = 2/width;
    r[1] = 0;
    r[2] = 0;
    r[3] = 0;
    r[4] = 0;
    r[5] = 2/height;
    r[6] = 0;
    r[7] = 0;
    r[8] = 0;
    r[9] = 0;
    r[10] = -(2/(far-near));
    r[11] = 0;
    r[12] = 0;
    r[13] = 0;
    r[14] = -((far+near)/(far-near));
    r[15] = 1;

    Matrix4x4* result = new Matrix4x4(r);
    return result;
}



