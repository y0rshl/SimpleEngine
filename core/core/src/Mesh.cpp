//
//  Mesh.cpp
//  core
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright © 2016 ITBA. All rights reserved.
//

#include "Mesh.hpp"

void Mesh::Load() {

    
    // Declare the path and filename of the file containing the scene.
    // In this case, we are assuming the file is in the same directory as the executable.
    const char* lFilename = "box.fbx";
    
}

shared_ptr<Mesh> Mesh::createBox() {
    shared_ptr<Mesh> mesh = make_shared<Mesh>();

    //create vao
    glGenVertexArrays(1, &mesh->m_vertexArrayID);
    glBindVertexArray(mesh->m_vertexArrayID);

    static const GLfloat positionData[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    //create vbo
    glGenBuffers(1, &mesh->m_positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);


    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_positionBuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    glBindVertexArray(0); // Unbind our Vertex Array Object

    return mesh;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &m_positionBuffer);
    glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Mesh::use() {
    glBindVertexArray(m_vertexArrayID);
}
