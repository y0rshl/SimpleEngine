//
// Created by Andrea Lata on 8/18/16.
//

#ifndef SIMPLEENGINE_CAMERA_H
#define SIMPLEENGINE_CAMERA_H

#include "Component.hpp"
#include "Transform.hpp"

class Camera : Component {

    bool invertColumnMajor(float m[16], float invOut[16]);

public:
    bool enabled;

    Camera();
    void update(double dt);

    void setSO(SceneObject so);

    Matrix4x4* getViewMatrix();
};


#endif //SIMPLEENGINE_CAMERA_H
