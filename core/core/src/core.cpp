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
#include "../test/JsonTest.hpp"
#include "../test/MatrixTest.hpp"
#include "Matrix4x4.hpp"
#include "Engine.hpp"
#include "../test/SceneObjectTest.hpp"
#include "RenderPass.hpp"

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
	 * My Matrix to test inverse
	 */
	//Identity
	float array[16] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	Matrix4x4* matrix = new Matrix4x4(array);
	matrix->toString();
	printf("\n Invirtiendo... \n");
	Matrix4x4* inverse = matrix->inverse();
	printf("\n Inversa lista!\n");
	inverse->toString();

	// OTra
	float array2[16] = {1.0, 1.0, 1.0, 1.0, 2.0, 1.0, -1.0, -2.0, 1.0, -1.0, -1.0, 1.0, 1.0, -2.0, 2.0, -1.0};
	Matrix4x4* matrix2 = new Matrix4x4(array2);
	matrix2->toString();
	printf("\n Invirtiendo... \n");
	Matrix4x4* inverse2 = matrix2->inverse();
	printf("\n Inversa lista!\n");
	inverse2->toString();

    /**
     * Test matrix
     */
	MatrixTest* matrixTest = new MatrixTest();
	matrixTest->testMatrix();

    /**
     * Test SceneObjectTree
     */

    SceneObjectTest* sceneObjectTest = new SceneObjectTest;
    sceneObjectTest->testSceneTree();

    /**
     * Test json
     */

//    JsonTest* jsonTest = new JsonTest();
//    jsonTest->parseJson();
//	return 0;

	RenderPass* renderPass = new RenderPass();
	renderPass->setViewport(200,200,200,200);
	renderPass->execute();
    Engine engine;
    engine.run();

    return 0;
}

