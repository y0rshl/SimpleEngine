//
// Created by Andrea Lata on 11/25/16.
//

#ifndef SIMPLEENGINE_CAMERA_HPP
#define SIMPLEENGINE_CAMERA_HPP

#include "Component.hpp"
#include "Matrix4x4.hpp"
#include "Vec4.hpp"

class Camera : public Component {

    bool enabled;

    void update(double dt);

    //void setSO(SceneObject so);

    Vec4 getPosition(); //un punto

    virtual Matrix4x4* getProjectionMatrix() = 0;

public:
    Camera();
};


#endif //SIMPLEENGINE_CAMERA_HPP
