//
//  Matrix4x4.hpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#ifndef Matrix4x4_hpp
#define Matrix4x4_hpp
#define SIZE 4

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <vector>

/**
 * Row-major matrix
 **/
class Matrix4x4 {
public:

    Matrix4x4(float[SIZE][SIZE]);

    std::vector<std::vector<float>> getValues();
    Matrix4x4* operator+(const Matrix4x4&);
    Matrix4x4* operator*(const Matrix4x4&);
    std::vector<std::vector<float>> matrix;


private:
};
#endif /* Matrix4x4_hpp */
