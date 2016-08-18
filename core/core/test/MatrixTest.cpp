//
// Created by Leonel Badi on 8/8/16.
//

#include "MatrixTest.hpp"

void MatrixTest::testMatrix(){
    float values[16] = {
            1,2,3,4,
            5,6,7,8,
            1,2,3,4,
            5,6,7,8
    };
    Matrix4x4* matrix4x4 = new Matrix4x4(values);
    float* vals = matrix4x4->getValues();
    Matrix4x4* matrixSum = (*matrix4x4)+(*matrix4x4);
    float* sumVals = matrixSum->getValues();

//    printf("Values : \n");
//    for(int i = 0 ; i < 4 ; i++){
//        for(int j = 0 ; j < 4 ; j++){
//            printf(" %f ", vals[i][j]);
//        }
//        printf("\n");
//    }
//    printf(" Sum Values : \n");
//    for(int i = 0 ; i < 4 ; i++){
//        for(int j = 0 ; j < 4 ; j++){
//            printf(" %f ", sumVals[i][j]);
//        }
//        printf("\n");
//    }

    Matrix4x4* matrixMult = (*matrix4x4)*(*matrix4x4);
    float* multVals = matrixMult->getValues();

//    printf(" Mult Values : \n");
//    for(int i = 0 ; i < 4 ; i++){
//        for(int j = 0 ; j < 4 ; j++){
//            printf(" %f ", multVals[i][j]);
//        }
//        printf("\n");
//    }
}