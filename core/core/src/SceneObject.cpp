//
//  SceneObject.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include <Matrix4x4.hpp>
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
