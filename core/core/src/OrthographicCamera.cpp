//
// Created by paul on 18/08/16.
//

#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(float width, float height, float near, float far) {
    this->width = width;
    this->height = height;
    this->near = near;
    this->far = far;

}

Matrix4x4* OrthographicCamera::getViewMatrix(){

}

Matrix4x4* OrthographicCamera::getProjectionMatrix(){
    float r[16];

    r[0] = 1/width;
    r[1] = 0;
    r[2] = 0;
    r[3] = 0;
    r[4] = 0;
    r[5] = 1/height;
    r[6] = 0;
    r[7] = 0;
    r[8] = 0;
    r[9] = 0;
    r[10] = -(2/(far-near));
    r[11] = -(far+near/(far-near));
    r[12] = 0;
    r[13] = 0;
    r[14] = 0;
    r[15] = 1;

    Matrix4x4* result = new Matrix4x4(r);
    return result;
}

void OrthographicCamera::setWidth(float width) {
    OrthographicCamera::width = width;
}

void OrthographicCamera::setHeight(float height) {
    OrthographicCamera::height = height;
}

void OrthographicCamera::setNear(float near) {
    OrthographicCamera::near = near;
}

void OrthographicCamera::setFar(float far) {
    OrthographicCamera::far = far;
}
