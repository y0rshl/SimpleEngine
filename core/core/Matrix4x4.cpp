//
//  Matrix4x4.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include <vector>
#include "Matrix4x4.hpp"


std::vector<std::vector<float>> Matrix4x4::getValues() {
    return matrix;
}

Matrix4x4::Matrix4x4(float val[SIZE][SIZE] ) {
    matrix = std::vector<std::vector<float>>(SIZE, std::vector<float>(SIZE, 0));
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            matrix[i][j] = val[i][j];
        }
    }

}

Matrix4x4* Matrix4x4::operator+(const Matrix4x4& matrix){
    std::vector<std::vector<float>> valsMatrix = matrix.matrix;
    std::vector<std::vector<float>> vals = this->matrix;
    float sumVals[SIZE][SIZE];

    for(int i = 0 ; i<valsMatrix.size() ; i++){
        for(int j = 0 ; j<valsMatrix[i].size() ; j++){
            sumVals[i][j] = vals[i][j] + valsMatrix[i][j];
        }
    }
    Matrix4x4* result = new Matrix4x4(sumVals);
    return result;
}


