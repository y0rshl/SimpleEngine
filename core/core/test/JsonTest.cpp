//
// Created by Leonel Badi on 8/8/16.
//

#include "JsonTest.hpp"

using json = nlohmann::json;
json JsonTest::parseJson() {
    std::ifstream is;
    is.open("/Users/leonelbadi/Documents/workspace/SimpleEngine/core/core/in.json", std::ios::in);
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];
    //Read into buffer
    is.read(buffer,length);

    json j2 = json::parse(buffer);
    std::cout << j2.dump(4) << std::endl;
//    std::cout << str << std::endl;
}