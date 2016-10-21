//
//  SceneObject.hpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "Transform.hpp"
#include "Component.hpp"

using namespace std;

class SceneObject : public enable_shared_from_this<SceneObject> {
    
public:
    vector<shared_ptr<SceneObject>> m_children;
    weak_ptr<SceneObject> parent;
    
    shared_ptr<Transform> m_transform;

    vector<shared_ptr<Component>> m_components;

public:

    SceneObject();

    Matrix4x4* getPosition();

    void update(double dt);

    void addComponent(shared_ptr<Component> component);

    //TODO agregar getViewMatrix
};

#endif /* SceneObject_hpp */
