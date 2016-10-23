//
// Created by SANDSTORM04 on 8/18/16.
//

#ifndef SIMPLEENGINE_RENDERPASS_HPP
#define SIMPLEENGINE_RENDERPASS_HPP


#include <GL/glew.h>
#include <memory>
#include <SceneObject.hpp>
#include "DirectionalLight.hpp"
#include "Camera.h"

class RenderPass {

public:
    void execute();
    void setViewport(int viewportX, int viewportY, int viewportWidth, int viewportHeight);
protected:
    int viewportX;
    int viewportY;
    int viewportWidth;
    int viewportHeight;

private:
    void initContext();

    void createSceneObject (const std::__1::shared_ptr <SceneObject> &meshSceneObject,
                            float x, float y, float z,
                            float rx, float ry, float rz,
                            float sx, float sy, float sz);

    Matrix4x4 *getMVPLight (shared_ptr<SceneObject> &meshSceneObject , shared_ptr<SceneObject> &lightSceneObject ,
                       shared_ptr<DirectionalLight> &dl);

    Matrix4x4 *getMVPCamera (shared_ptr<SceneObject> &meshSceneObject , shared_ptr<SceneObject> &camSceneObject ,
            shared_ptr<Camera> &cam);

    shared_ptr<Camera> setCamera (shared_ptr<SceneObject> camSceneObject , int camera,
                                  float width, float height, float far, float near);
};


#endif //SIMPLEENGINE_RENDERPASS_HPP
