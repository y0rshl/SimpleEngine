//
// Created by SANDSTORM04 on 8/9/16.
//

#include "Engine.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <iostream>

using namespace std;

void Engine::run() {

    auto lastTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> targetFrameMs = std::chrono::nanoseconds{16666666};
    std::chrono::duration<double, std::milli> accumulatorMs = std::chrono::milliseconds{0};

    while (true) {
        auto current = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dt = current - lastTime;
        accumulatorMs += dt;
        while (accumulatorMs.count() > targetFrameMs.count()) {
            update(targetFrameMs.count());
            accumulatorMs -= targetFrameMs;
        }
        render();
        lastTime = current;

        //be nice
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Engine::update(double dt) {
    //std::cout << "f() took " << dt << " ms\n";
    //TODO: update systems
    //call update on App class
}

void Engine::render() {


}
