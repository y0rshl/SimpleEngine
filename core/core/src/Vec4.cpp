//
// Created by Andrea Lata on 9/8/16.
//

#include <cmath>
#include "Vec4.hpp"

Vec4::Vec4 (float *values) {
    for (int i = 0; i < 4; i++)
    {
        vec[i] = values[i];
    }
}

float *Vec4::getValues () {
    return vec;
}

Vec4 Vec4::normalize () {
    float norm = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] + vec[3] * vec[3]);
    return Vec4(new float[4]{vec[0]/norm,vec[1]/norm,vec[2]/norm,vec[3]/norm});;
}
