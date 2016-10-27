//
// Created by SANDSTORM04 on 8/18/16.
//

#ifndef SIMPLEENGINE_RENDERPASS_HPP
#define SIMPLEENGINE_RENDERPASS_HPP


#include <GL/glew.h>
#include "Mesh.hpp"
#include "SceneObject.hpp"
#include "shader.hpp"
#include <core/core/src/ShaderProgram.hpp>
#include "CameraComponent.hpp"

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
    void placeSceneObject(SceneObject* sceneObject, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
    void drawMesh(shared_ptr<Mesh> mesh, SceneObject* sceneObject, SceneObject* lightSceneObject, CameraComponent* camera, CameraComponent* lightCamera, shared_ptr<ShaderProgram> shaderProgram);
    void moveCamera(CameraComponent* camera, SceneObject* sceneObject);
};


#endif //SIMPLEENGINE_RENDERPASS_HPP
