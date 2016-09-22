//
// Created by Andrea Lata on 9/8/16.
//

#ifndef SIMPLEENGINE_VEC4_HPP
#define SIMPLEENGINE_VEC4_HPP


class Vec4 {
private:
    float vec[4];

public:
    Vec4(float x, float y, float z, float w);
    Vec4(float* values);

    float * getValues();

    Vec4 normalize ();
};


#endif //SIMPLEENGINE_VEC4_HPP
