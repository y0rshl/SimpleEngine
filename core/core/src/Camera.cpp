//
// Created by Andrea Lata on 11/25/16.
//

#include <core/core/sdk/Transform.hpp>
#include <core/core/sdk/SceneObject.hpp>
#include "Camera.hpp"

Camera::Camera () {
    enabled = true;
}

Vec4 Camera::getPosition () {
    shared_ptr<SceneObject> cam;

    cam = this->owner.lock();
    SceneObject *so = cam.get();

    shared_ptr<Transform> t = so->m_transform;
    return t.get()->get_position();
}

void Camera::update (double dt) {

}
