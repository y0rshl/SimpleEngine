//
//  Matrix4x4.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include <string>
#include <cmath>
#include "Matrix4x4.hpp"


float* Matrix4x4::getValues() {
    return &matrix[0];
}

Matrix4x4::Matrix4x4() {
    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = 1;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

Matrix4x4::Matrix4x4(const Matrix4x4 &obj) {
    memcpy(matrix, obj.matrix, sizeof(matrix));
}

Matrix4x4::Matrix4x4(float* values) {
    for (int i = 0; i < 16; i++)
    {
        matrix[i] = values[i];
    }
}

Matrix4x4* Matrix4x4::operator+(const Matrix4x4& matrix){
    const float* valsMatrix = &(matrix.matrix[0]);
    float* vals = this->matrix;
    float sumVals[16];

    for(int i = 0 ; i<16 ; i++){
        sumVals[i] = vals[i] + valsMatrix[i];
    }
    Matrix4x4* result = new Matrix4x4(&sumVals[0]);
    return result;
}

Matrix4x4* Matrix4x4::operator*(const Matrix4x4& matrix) {
    float* m1 = this->matrix;
    const float* m2 = matrix.matrix;
    float r[16];

    r[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
    r[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
    r[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
    r[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];

    r[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
    r[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
    r[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
    r[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];

    r[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
    r[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
    r[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
    r[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];

    r[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
    r[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
    r[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
    r[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];

    Matrix4x4* result = new Matrix4x4(r);
    return result;
}

Matrix4x4 Matrix4x4::makeScaleMatrix(float sx, float sy, float sz) {
    Matrix4x4 result;
    result.matrix[0] = sx;
    result.matrix[5] = sy;
    result.matrix[10] = sz;
    return result;
}

Matrix4x4 Matrix4x4::makeTranslationMatrix(float x, float y, float z) {
    Matrix4x4 result;
    result.matrix[3] = x;
    result.matrix[7] = y;
    result.matrix[11] = z;
    return result;
}

Matrix4x4 Matrix4x4::makeRotationMatrix(float rx, float ry, float rz) {
    Matrix4x4 result, mx, my, mz;

    mx.matrix[4] = float(cos(rx));
    mx.matrix[5] = float(sin(rx));
    mx.matrix[7] = float(-sin(rx));
    mx.matrix[8] = float(cos(rx));

    my.matrix[0] = float(cos(ry));
    my.matrix[2] = -float(sin(ry));
    my.matrix[6] = float(sin(ry));
    my.matrix[8] = float(cos(ry));

    my.matrix[0] = float(cos(rz));
    my.matrix[1] = float(sin(rz));
    my.matrix[3] = float(-sin(rz));
    my.matrix[4] = float(cos(rz));

    return *mx.operator*(my)->operator*(mz);
}

Matrix4x4* Matrix4x4::makeTRSMatrix(float x, float y, float z, float sx, float sy, float sz, float rx, float ry, float rz){
    Matrix4x4 t, r, s;
    t = makeTranslationMatrix(x,y,z);
    r = makeRotationMatrix(rx, ry, rz);
    s = makeScaleMatrix(sx, sy, sz);

    return t.operator*(r)->operator*(s);

}


std::string Matrix4x4::toString() {
    std::string str;
//    for(int i = 0 ; i < 16 ; i++){
//        char buff[100];
//        std::snprintf(buff, 100, " %f", matrix[i*4 + j]);
//
//        str.append(buff);
//        //printf("\n");
//    }
    return str;
}


