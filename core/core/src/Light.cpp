//
// Created by Andrea Lata on 9/8/16.
//

#include "Light.hpp"
#include <core/core/sdk/SceneObject.hpp>

Light::Light () {

}

Vec4 Light::getDirLight () {
    //Muliplico TRS * (0,0,1)
    shared_ptr<SceneObject> light;

    light = this->owner.lock();
    SceneObject *so = light.get();
    Matrix4x4 *trs = so->getPosition();

    Vec4 vec = trs->multVec4(this->vec4);
    return vec.normalize();
}

void Light::update (double dt) {

}
