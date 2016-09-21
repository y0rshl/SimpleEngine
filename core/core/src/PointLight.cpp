//
// Created by Andrea Lata on 9/21/16.
//

#include "PointLight.hpp"

PointLight::PointLight (Vec4 vec) {
    this->vec = vec;
}


Vec4 PointLight::getPosition () {
    //Muliplico TRS * (0,0,1)
//    shared_ptr<SceneObject> light;
//
//    light = this->owner.lock();
//    SceneObject *so = light.get();
//    Matrix4x4 *trs = so->getPosition();
//
//    Vec4 vec = trs->multVec4(this->vec4);
//    return vec.normalize(); //TODO el vector de posicion tambien va normalizado?
}

