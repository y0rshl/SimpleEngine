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
    float vec[] = {0, 0, 1, 0};
    float* ans = m->vecRightMultiplyOperator(vec);
    float aux = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    ans[0] = ans[0]/aux;
    ans[1] = ans[1]/aux;
    ans[2] = ans[2]/aux;
    return ans;
}