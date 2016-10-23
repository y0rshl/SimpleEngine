//
// Created by Andrea Lata on 8/18/16.
//

#include <core/core/sdk/SceneObject.hpp>
#include "Camera.h"


Camera::Camera(){
    enabled = true;
}

void Camera::update(double dt) {

}

Vec4 Camera::getPosition () {
    shared_ptr<SceneObject> cam;

    cam = this->owner.lock();
    SceneObject *so = cam.get();

    shared_ptr<Transform> t = so->m_transform;
    return t.get()->get_position();
}

/*void Camera::setSO (SceneObject so) {
    //Como crear/instanciar weak_ptr?
    this->owner = make_shared<SceneObject>(so);
}*/

