//
// Created by SANDSTORM04 on 8/18/16.
//

#include "RenderPass.hpp"
#include <opengl/gl.h>

void RenderPass::execute() {
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    glClearColor(1.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderPass::setViewport(int viewportX, int viewportY, int viewportWidth, int viewportHeight) {
    this->viewportX = viewportX;
    this->viewportY = viewportY;
    this->viewportWidth = viewportWidth;
    this->viewportHeight = viewportHeight;
}
