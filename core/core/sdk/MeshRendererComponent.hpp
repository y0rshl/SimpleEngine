//
// Created by paul on 18/08/16.
//

#ifndef SIMPLEENGINE_MESHRENDERERCOMPONENT_H
#define SIMPLEENGINE_MESHRENDERERCOMPONENT_H

#include "Component.hpp"

class MeshRendererComponent : Component {
public:
    bool enabled;
    void update(double dt);
};

#endif //SIMPLEENGINE_MESHRENDERERCOMPONENT_H
