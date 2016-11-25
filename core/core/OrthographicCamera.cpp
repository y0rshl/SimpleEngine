//
// Created by Andrea Lata on 11/25/16.
//

#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera (float width , float height , float near , float far) {
    this->width = width;
    this->height = height;
    this->far = far;
    this->near = near;
}

void OrthographicCamera::setWidth (float width) {
    this->width = width;
}

void OrthographicCamera::setHeight (float height) {
    this->height = height;
}

void OrthographicCamera::setFar (float far) {
    this->far = far;
}

void OrthographicCamera::setNear (float near) {
    this->near = near;
}

Matrix4x4 *OrthographicCamera::getProjectionMatrix () {
    float r[16];

    r[0] = 2/width;
    r[1] = 0;
    r[2] = 0;
    r[3] = 0;
    r[4] = 0;
    r[5] = 2/height;
    r[6] = 0;
    r[7] = 0;
    r[8] = 0;
    r[9] = 0;
    r[10] = -(2/(far-near));
    r[11] = 0;
    r[12] = 0;
    r[13] = 0;
    r[14] = -((far+near)/(far-near));
    r[15] = 1;

    Matrix4x4* result = new Matrix4x4(r);
    return result;
}
