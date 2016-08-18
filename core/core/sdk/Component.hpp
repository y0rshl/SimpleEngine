//
// Created by SANDSTORM04 on 8/11/16.
//

#ifndef SIMPLEENGINE_COMPONENT_HPP
#define SIMPLEENGINE_COMPONENT_HPP

#include <memory>

using namespace std;

class SceneObject;

class Component {

    weak_ptr<SceneObject> owner;

public:
    virtual void update(double dt) = 0;

};


#endif //SIMPLEENGINE_COMPONENT_HPP
