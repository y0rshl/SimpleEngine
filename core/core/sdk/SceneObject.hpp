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
#include "Transform.hpp"

class SceneObject {
    
public:
    std::vector<std::shared_ptr<SceneObject>> m_children;
    std::weak_ptr<SceneObject> parent;
    
    std::shared_ptr<Transform> m_transform;
    
public:
    Matrix4x4* getPosition();
};

#endif /* SceneObject_hpp */
