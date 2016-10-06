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

Matrix4x4* Camera::getViewMatrix() {
    //this.owner.m_transform.inverse()
    shared_ptr<SceneObject> cam;

    cam = this->owner.lock();

    SceneObject *so = cam.get();

    Matrix4x4* m = so->getPosition();
    float* inverse = new float[16];
    if(Matrix4x4::invertColumnMajor(m->getValues(), inverse)){
        return new Matrix4x4(inverse);
    }

    //nunca deberia salir por aca
    return nullptr;
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

