//
// Created by paul on 06/09/16.
//

#include "core/core/sdk/lights/PointLight.hpp"
#include "SceneObject.hpp"

PointLight::PointLight(weak_ptr<SceneObject> _owner){
    this->owner = _owner;
}

void PointLight::update(double dt){

}

float* PointLight::getPosition() {
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