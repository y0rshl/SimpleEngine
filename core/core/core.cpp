/*
 *  core.cpp
 *  core
 *
 *  Created by SANDSTORM04 on 7/23/16.
 *  Copyright © 2016 ITBA. All rights reserved.
 *
 */

#include <iostream>
#include "core.hpp"
#include "corePriv.hpp"

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

