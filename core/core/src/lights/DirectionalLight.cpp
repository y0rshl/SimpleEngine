//
// Created by paul on 06/09/16.
//

#include "core/core/sdk/lights/DirectionalLight.hpp"
#include "SceneObject.hpp"

DirectionalLight::DirectionalLight(weak_ptr<SceneObject> _owner){
    this->owner = _owner;
}

void DirectionalLight::update(double dt){

}

float* DirectionalLight::getDirection(){
    shared_ptr<SceneObject> cam;
    SceneObject *sceneObject;
    Matrix4x4* m;

    cam = this->owner.lock();
    sceneObject = cam.get();
    m = sceneObject->getPosition();
    float *vec = new float[0, 0, 1, 0];
    return m->vecRightMultiplyOperator(vec);
}