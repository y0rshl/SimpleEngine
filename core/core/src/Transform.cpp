//
//  Transform.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include "Matrix4x4.hpp"
#include "Transform.hpp"


Transform::Transform(){
}

Transform::Transform(Matrix4x4* TRS){
    this->TRS = TRS;
}

void Transform::set_position (float x , float y , float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Transform::set_rotation(float rx, float ry, float rz){
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
}

void Transform::set_scale(float sx, float sy, float sz){
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

void Transform::set_TRS(Matrix4x4* TRS){
    this->TRS = TRS;
};

void Transform::refreshTRS(){
    this->TRS = TRS->makeTRSMatrix(x,y,z,rx,ry,rz,sx,sy,sz);
}

Vec4 Transform::get_position(){
    return Vec4(x,y,z,0);
}
