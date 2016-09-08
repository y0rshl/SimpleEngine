//
//  Matrix4x4.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include <cstring>
#include "Matrix4x4.hpp"
#include "cmath"


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

float* Matrix4x4::vecRightMultiplyOperator(const float vec[]){
    // TODO: Check vec size to avoid errors
    float* ans = new float[4];
    float* m1 = this->matrix;
    printf("%f %f\n", ans[0], m1[0]);
    ans[0] = m1[0]*vec[0] + m1[4]*vec[1] + m1[8]*vec[2] + m1[12]*vec[3];
    ans[1] = m1[1]*vec[0] + m1[5]*vec[1] + m1[9]*vec[2] + m1[13]*vec[3];
    ans[2] = m1[2]*vec[0] + m1[6]*vec[1] + m1[10]*vec[2] + m1[14]*vec[3];
    ans[3] = m1[3]*vec[0] + m1[7]*vec[1] + m1[11]*vec[2] + m1[15]*vec[3];
    return ans;
}

Matrix4x4* Matrix4x4::inverse() {
    float inv[16], det;
    int i;
    float* m = matrix;
    float invOut[16];

    inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
    inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
    inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
    inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
    inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
    inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
    inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
    inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
    inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
    inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
    inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
    inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if(det == 0) {
        printf("\n[WARNING] Matrix has no inverse. Null returned.\n");
        return nullptr;
    }

    det = 1.f / det;

    for(i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return new Matrix4x4(invOut);
}

std::string Matrix4x4::toString() {
    std::string str;
    for(int i = 0 ; i < 16 ; i++) {
        printf("%f ",matrix[i]);
    }
//    for(int i = 0 ; i < 16 ; i++){
//        char buff[100];
//        std::snprintf(buff, 100, " %f", matrix[i*4 + j]);
//
//        str.append(buff);
//        //printf("\n");
//    }
    return str;
}

Matrix4x4 Matrix4x4::makeTranslationMatrix(float x, float y, float z) {
    Matrix4x4 result;
    result.matrix[12] = x;
    result.matrix[13] = y;
    result.matrix[14] = z;
    return result;
}

Matrix4x4 Matrix4x4::makeRotationMatrix(float rx, float ry, float rz) {
    Matrix4x4 mx, my, mz;
    mx.matrix[5] = float(cos(rx));
    mx.matrix[6] = float(sin(rx));
    mx.matrix[9] = float(-sin(rx));
    mx.matrix[10] = float(cos(rx));

    my.matrix[0] = float(cos(ry));
    my.matrix[2] = -float(sin(ry));
    my.matrix[8] = float(sin(ry));
    my.matrix[10] = float(cos(ry));

    mz.matrix[0] = float(cos(rz));
    mz.matrix[1] = float(sin(rz));
    mz.matrix[4] = float(-sin(rz));
    mz.matrix[5] = float(cos(rz));
    return *mx.operator*(my)->operator*(mz);
}

Matrix4x4 Matrix4x4::makeScaleMatrix(float sx, float sy, float sz) {
    Matrix4x4 result;
    result.matrix[0] = sx;
    result.matrix[5] = sy;
    result.matrix[10] = sz;
    return result;
}

Matrix4x4* Matrix4x4::makeTRS(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {
    Matrix4x4 t = makeTranslationMatrix(x, y, z);
    Matrix4x4 r = makeRotationMatrix(rx, ry, rz);
    Matrix4x4 s = makeScaleMatrix(sx, sy, sz);
    return t.operator*(r)->operator*(s);
}
