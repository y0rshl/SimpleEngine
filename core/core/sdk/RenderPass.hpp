//
// Created by SANDSTORM04 on 8/18/16.
//

#ifndef SIMPLEENGINE_RENDERPASS_HPP
#define SIMPLEENGINE_RENDERPASS_HPP


#include <GL/glew.h>
#include <memory>
#include <SceneObject.hpp>

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
                            float sx, float sy, float sz) const;
};


#endif //SIMPLEENGINE_RENDERPASS_HPP
