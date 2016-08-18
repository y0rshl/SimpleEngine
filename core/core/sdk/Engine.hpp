//
// Created by SANDSTORM04 on 8/9/16.
//

#ifndef SIMPLEENGINE_ENGINE_HPP
#define SIMPLEENGINE_ENGINE_HPP

#include <memory>

class Engine {

public:
    void run();

protected:
    void update(double dt);
    void render();
};

#endif //SIMPLEENGINE_ENGINE_HPP
