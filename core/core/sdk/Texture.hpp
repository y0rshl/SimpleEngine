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

    void bind(GLuint location);

private:
    GLuint m_textureId;
};


#endif //SIMPLEENGINE_TEXTURE_H
