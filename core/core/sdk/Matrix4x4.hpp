//
//  Matrix4x4.hpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#ifndef Matrix4x4_hpp
#define Matrix4x4_hpp

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <vector>

/**
 * Column-major matrix
 **/
class Matrix4x4 {
public:

    Matrix4x4();
    Matrix4x4(float* values);
    Matrix4x4(const Matrix4x4 &obj);  // copy constructor

    float* getValues();
    Matrix4x4* operator+(const Matrix4x4&);
    Matrix4x4* operator*(const Matrix4x4&);
//    std::vector<std::vector<float>> matrix;

    static Matrix4x4 makeScaleMatrix(float sx, float sy, float sz);

    std::string toString();
private:
    float matrix[16];
};
#endif /* Matrix4x4_hpp */
