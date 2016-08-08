//
// Created by Leonel Badi on 8/8/16.
//

#ifndef SIMPLEENGINE_JSONTEST_H
#define SIMPLEENGINE_JSONTEST_H

#include "json.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>

using json = nlohmann::json;
class JsonTest {
public:
    json parseJson();
};


#endif //SIMPLEENGINE_JSONTEST_H
