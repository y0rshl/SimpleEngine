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
#include "Vec4.hpp"

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
    static Matrix4x4 makeTranslationMatrix(float x, float y, float z);
    static Matrix4x4 makeRotationMatrix(float rx, float ry, float rz);
    static Matrix4x4* makeTRSMatrix(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);

    static bool invertColumnMajor(float m[16], float invOut[16]);

    Vec4 multVec4(Vec4 vec4);

    std::string toString();
private:
    float* mVec4(float * vec4);
    float matrix[16];
};
#endif /* Matrix4x4_hpp */
