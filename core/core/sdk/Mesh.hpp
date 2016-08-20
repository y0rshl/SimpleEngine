//
//  Mesh.hpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <memory>
#include <GL/glew.h>
#include <opengl/gl.h>

using namespace std;

class Mesh {
    
public:
    static void Load();

    static shared_ptr<Mesh> createBox();

    ~Mesh();

    void use();

private:
    GLuint m_positionBuffer;
    GLuint m_vertexArrayID;
};

#endif /* Mesh_hpp */
