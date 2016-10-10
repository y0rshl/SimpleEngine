//
//  Transform.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include "Matrix4x4.hpp"
#include "Transform.hpp"


Transform::Transform(Matrix4x4* TRS){
    this->TRS = TRS;
}

Transform::Transform(){

}

void Transform::setPosition(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Transform::setRotation(float rx, float ry, float rz) {
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
}

void Transform::setScale(float sx, float sy, float sz) {
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

float* Transform::getRotation(){
    float* rotation = new float[3];
    rotation[0] = this->rx;
    rotation[1] = this->ry;
    rotation[2] = this->rz;
    return rotation;
}

void Transform::refreshTRS() {
    Matrix4x4 *trs;
    this->TRS = trs->makeTRS( x, y, z, rx, ry, rz, sx, sy, sz);
}
