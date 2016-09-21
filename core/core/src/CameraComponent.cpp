//
// Created by paul on 18/08/16.
//

#include "CameraComponent.hpp"
#include "SceneObject.hpp"


Matrix4x4* CameraComponent::getViewMatrix(){
    shared_ptr<SceneObject> cam;
    SceneObject *sceneObject;
    Matrix4x4* m;

    cam = this->owner.lock();
    sceneObject = cam.get();
    m = sceneObject->getPosition();

    return m->inverse();
}

void CameraComponent::update(double dt){

}

float* CameraComponent::getPosition() {
    shared_ptr<SceneObject> cam;
    SceneObject *sceneObject;
    Matrix4x4* m;

    cam = this->owner.lock();
    sceneObject = cam.get();
    m = sceneObject->getPosition();
    float vec[] = {0, 0, 0, 1};
    float* ans = m->vecRightMultiplyOperator(vec);
    return ans;
}