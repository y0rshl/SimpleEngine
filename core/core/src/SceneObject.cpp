//
//  SceneObject.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include "Matrix4x4.hpp"
#include "SceneObject.hpp"

/**
 * Get the position of the sceneObject. This will go through the tree recursively asking for the father position.
 * @return Matrix4x4*:the position of the sceneObject
 */
Matrix4x4* SceneObject::getPosition() {
    auto spParent = this->parent.lock();
    if (spParent) {
        return (*spParent->getPosition()) * (*this->m_transform->TRS);
    }

    return this->m_transform->TRS;
}

void update(double dt) {
    //for each Component
    //c->update(dt);
}

SceneObject::SceneObject(){
    m_transform = make_shared<Transform>();
}

void SceneObject::addComponent(shared_ptr<Component> component) {
    m_components.push_back(component);
    component->owner = shared_from_this();
}

Matrix4x4* SceneObject::getViewMatrix() {

    SceneObject *so = this;

    Matrix4x4* m = so->getPosition();
    float* inverse = new float[16];
    if(Matrix4x4::invertColumnMajor(m->getValues(), inverse)){
        return new Matrix4x4(inverse);
    }

    //nunca deberia salir por aca
    return nullptr;
}