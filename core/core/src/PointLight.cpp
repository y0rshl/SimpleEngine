//
// Created by Andrea Lata on 9/21/16.
//

#include "PointLight.hpp"
#include <core/core/sdk/SceneObject.hpp>

PointLight::PointLight () {

}

Vec4 PointLight::getPosition () {
    shared_ptr<SceneObject> light;

    light = this->owner.lock();
    SceneObject *so = light.get();

    shared_ptr<Transform> t = so->m_transform;
    return t.get()->get_position();
}



