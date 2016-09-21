//
// Created by Andrea Lata on 9/8/16.
//

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
