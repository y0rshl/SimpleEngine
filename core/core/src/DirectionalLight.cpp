//
// Created by Andrea Lata on 9/8/16.
//

#include "DirectionalLight.hpp"
#include <core/core/sdk/SceneObject.hpp>

DirectionalLight::DirectionalLight() {
}

Vec4 DirectionalLight::getDirLight () {
    //Muliplico TRS * (0,0,1)
    shared_ptr<SceneObject> light;

    light = this->owner.lock();
    SceneObject *so = light.get();
    Matrix4x4 *trs = so->getPosition();

    return trs->multVec4(this->vec4); //con esta multiplicacion te quedas con el vector z (q es hacia donde apunta el objeto)
}

