//
// Created by Andrea Lata on 8/18/16.
//

#include <cmath>
#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fovX, float fovY, float near, float far) {
    this->fovX = fovX;
    this->fovY = fovY;
    this->near = near;
    this->far = far;
}

void PerspectiveCamera::setFovX(float fovX) {
    PerspectiveCamera::fovX = fovX;
}

void PerspectiveCamera::setFovY(float fovY) {
    PerspectiveCamera::fovY = fovY;
}

void PerspectiveCamera::setNear(float near) {
    PerspectiveCamera::near = near;
}

void PerspectiveCamera::setFar(float far) {
    PerspectiveCamera::far = far;
}

Matrix4x4* PerspectiveCamera::getProjectionMatrix() {
    float r[16];

    //r[0] = atan(fovX/2);
    r[0] = 1/tanf(fovX/2);
    r[1] = 0;
    r[2] = 0;
    r[3] = 0;
    r[4] = 0;
    //r[5] = atan(fovY/2);
    r[5] = 1/tanf(fovY/2);
    r[6] = 0;
    r[7] = 0;
    r[8] = 0;
    r[9] = 0;
    r[10] = -((far+near)/(far-near));
    r[11] = -1;
    r[12] = 0;
    r[13] = 0;
    r[14] = -(2*far*near)/(far-near);
    r[15] = 0;

    Matrix4x4* result = new Matrix4x4(r);
    return result;
}


