//
// Created by SANDSTORM04 on 8/18/16.
//

#ifndef SIMPLEENGINE_RENDERPASS_HPP
#define SIMPLEENGINE_RENDERPASS_HPP


class RenderPass {

public:
    void execute();
    void setViewport(int viewportX, int viewportY, int viewportWidth, int viewportHeight);
protected:
    int viewportX;
    int viewportY;
    int viewportWidth;
    int viewportHeight;
};


#endif //SIMPLEENGINE_RENDERPASS_HPP
