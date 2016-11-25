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
#include "Vec4.hpp"

class Transform {
    
    float x, y, z;
    float rx, ry, rz;
    float sx, sy, sz;

public:
    Matrix4x4* TRS;

    Transform(Matrix4x4* TRS);

    Transform();

    void set_TRS(Matrix4x4 *TRS);

    void set_position (float x , float y , float z);

    void set_rotation(float rx, float ry, float rz);

    void set_scale(float sx, float sy, float sz);

    Vec4 get_position();

    Vec4 get_rotation();

    void refreshTRS();
};

#endif /* Transform_hpp */
