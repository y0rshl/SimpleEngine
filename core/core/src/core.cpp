/*
 *  core.cpp
 *  core
 *
 *  Created by SANDSTORM04 on 7/23/16.
 *  Copyright © 2016 ITBA. All rights reserved.
 *
 */

#include <iostream>
#include <vector>
#include <list>
#include "core.hpp"
#include "corePriv.hpp"
#include "Matrix4x4.hpp"
#include "Engine.hpp"

using namespace std;
void core::HelloWorld(const char * s)
{
	 corePriv *theObj = new corePriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void corePriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

int main( int argc, const char* argv[] )
{
	corePriv corePriv1;
	corePriv1.HelloWorldPriv("HOLA!");
	float values[4][4] = {
			{1,2,3,4},
			{5,6,7,8},
			{1,2,3,4},
			{5,6,7,8}
	};
	Matrix4x4* matrix4x4 = new Matrix4x4(values);
	std::vector<std::vector<float>> vals = matrix4x4->getValues();
    Matrix4x4* matrixSum = (*matrix4x4)+(*matrix4x4);
    std::vector<std::vector<float>> sumVals = matrixSum->getValues();

    printf("Values : \n");
	for(int i = 0 ; i < 4 ; i++){
		for(int j = 0 ; j < 4 ; j++){
			printf(" %f ", vals[i][j]);
		}
        printf("\n");
	}
    printf(" Sum Values : \n");
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            printf(" %f ", sumVals[i][j]);
        }
        printf("\n");
    }

    Engine engine;
    engine.run();

    return 0;

	for(int i=0;i<4*4.;i++){
		cout << vals[i][i];
		printf( "%f", vals[i][i] );
	}
	printf( "\nHello World\n\n" );
}

