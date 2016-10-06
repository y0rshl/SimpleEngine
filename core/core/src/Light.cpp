//
// Created by Andrea Lata on 9/8/16.
//

#include "Light.hpp"
#include <core/core/sdk/SceneObject.hpp>

Light::Light () {

}

void Light::update (double dt) {

}

Matrix4x4 *Light::getViewMatrix () {
    //this.owner.m_transform.inverse()
    shared_ptr<SceneObject> light;

    light = this->owner.lock();

    SceneObject *so = light.get();

    Matrix4x4* m = so->getPosition();
    float* inverse = new float[16];
    if(Matrix4x4::invertColumnMajor(m->getValues(), inverse)){
        return new Matrix4x4(inverse);
    }

    //nunca deberia salir por aca
    return nullptr;
}
