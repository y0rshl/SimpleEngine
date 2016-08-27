//
// Created by paul on 18/08/16.
//

#include "CameraComponent.hpp"


Matrix4x4* CameraComponent::getViewMatrix(){

    shared_ptr<SceneObject> cam;
    cam = this->owner.lock();

    SceneObject *sceneObject = cam.get();

    Matrix4x4* m = sceneObject->getPosition();
    return m->inverse();

}

void CameraComponent::update(double dt){

}