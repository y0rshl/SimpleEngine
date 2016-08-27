//
// Created by Andrea Lata on 8/18/16.
//

#ifndef SIMPLEENGINE_MESHRENDERER_H
#define SIMPLEENGINE_MESHRENDERER_H

#include "Component.hpp"

class MeshRenderer : Component {

public:
    bool enabled;

    MeshRenderer();
    void update(double dt);
};


#endif //SIMPLEENGINE_MESHRENDERER_H
