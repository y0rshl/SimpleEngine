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

float* CameraComponent::getDirection(){
    shared_ptr<SceneObject> cam;
    SceneObject *sceneObject;
    Matrix4x4* m;

    cam = this->owner.lock();
    sceneObject = cam.get();
    m = sceneObject->getPosition();
    float vec[] = {0, 0, 1, 0};
    float* ans = m->vecRightMultiplyOperator(vec);
    float aux = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    ans[0] = ans[0]/aux;
    ans[1] = ans[1]/aux;
    ans[2] = ans[2]/aux;
    return ans;
}

float* CameraComponent::getHorizontalDirection(){
    shared_ptr<SceneObject> cam;
    SceneObject *sceneObject;
    Matrix4x4* m;

    cam = this->owner.lock();
    sceneObject = cam.get();
    m = sceneObject->getPosition();
    float vec[] = {1, 0, 0, 0};
    float* ans = m->vecRightMultiplyOperator(vec);
    float aux = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    ans[0] = ans[0]/aux;
    ans[1] = ans[1]/aux;
    ans[2] = ans[2]/aux;
    return ans;
}

float* CameraComponent::getRotation(){
    shared_ptr<SceneObject> cam;
    SceneObject *sceneObject;
    Matrix4x4* m;

    cam = this->owner.lock();
    sceneObject = cam.get();
    m = sceneObject->getPosition();
    float vec[] = {1, 0, 0, 0};
    float* ans = m->vecRightMultiplyOperator(vec);
    float aux = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    ans[0] = ans[0]/aux;
    ans[1] = ans[1]/aux;
    ans[2] = ans[2]/aux;
    return ans;
}