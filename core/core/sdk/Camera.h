//
// Created by Andrea Lata on 8/18/16.
//

#ifndef SIMPLEENGINE_CAMERA_H
#define SIMPLEENGINE_CAMERA_H

#include "Component.hpp"
#include "Transform.hpp"

class Camera : public Component {

public:
    bool enabled;

    Camera();
    void update(double dt);

    //void setSO(SceneObject so);

    Vec4 getPosition(); //un punto

    virtual Matrix4x4* getProjectionMatrix() = 0;
};


#endif //SIMPLEENGINE_CAMERA_H
