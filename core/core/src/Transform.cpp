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
