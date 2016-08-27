//
//  Transform.hpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include <memory>
#include <vector>
#include "Matrix4x4.hpp"

class Transform {
    
    float x, y, z;
    float rx, ry, rz;
    float sx, sy, sz;

public:
    Matrix4x4* TRS;
    Transform();
    Transform(Matrix4x4* TRS);
    void setPosition(float x, float y, float z);
    void setRotation(float rx, float ry, float rz);
    void setScale(float sx, float sy, float sz);
};

#endif /* Transform_hpp */
