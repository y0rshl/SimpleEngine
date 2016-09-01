//
// Created by Leonel Badi on 25/8/16.
//

#ifndef SIMPLEENGINE_TEXTURE_H
#define SIMPLEENGINE_TEXTURE_H

#include <memory>

using namespace std;

class Texture {
public:

    static shared_ptr<Texture> loadBMP(const char * imagepath);

    GLuint texture_id;

private:
};


#endif //SIMPLEENGINE_TEXTURE_H
