//
//  Matrix4x4.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include "Matrix4x4.hpp"


std::vector<std::vector<float>> Matrix4x4::getValues() {
    return matrix;
}

Matrix4x4::Matrix4x4() {
    matrix = std::vector<std::vector<float>>(SIZE, std::vector<float>(SIZE, 0));
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

Matrix4x4::Matrix4x4(float val[SIZE][SIZE] ) {
    matrix = std::vector<std::vector<float>>(SIZE, std::vector<float>(SIZE, 0));
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
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

Matrix4x4* Matrix4x4::operator*(const Matrix4x4& matrix) {
    std::vector<std::vector<float>> valsMatrix = matrix.matrix;
    std::vector<std::vector<float>> vals = this->matrix;
    float multVals[SIZE][SIZE];

    for (int x = 0; x < 4; x++) { // row number of output
        for (int y = 0; y < 4; y++) { // column number of output
            multVals[x][y] = 0;
            for (int z = 0; z < 4; z++) { // four elements are added for this output
                multVals[x][y] += valsMatrix[x][z] * vals[z][y];
            }
        }
    }

    Matrix4x4* result = new Matrix4x4(multVals);
    return result;
}


