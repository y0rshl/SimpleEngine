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
#include "JsonTest.hpp"
#include "test/MatrixTest.hpp"
#include "Matrix4x4.hpp"

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

    /**
     * Test matrix
     */
	MatrixTest* matrixTest = new MatrixTest();
	matrixTest->testMatrix();

    /**
     * Test json
     */

    JsonTest* jsonTest = new JsonTest();
    jsonTest->parseJson();
	return 0;

}

