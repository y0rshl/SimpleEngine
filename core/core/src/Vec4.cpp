//
// Created by Andrea Lata on 11/25/16.
//

#include "Vec4.hpp"

Vec4::Vec4 (float x , float y , float z , float w) {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;
}

Vec4::Vec4 (float *values) {
    for (int i = 0; i < 4; i++)
    {
        vec[i] = values[i];
    }
}

float *Vec4::getValues () {
    return vec;
}


