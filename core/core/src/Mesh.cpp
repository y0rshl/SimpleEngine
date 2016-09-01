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


//    static const GLfloat positionData[] = {
//            -0.5f, -1.0f, 0.0f,
//            1.0f, -1.0f, 0.0f,
//            0.0f, 1.0f, 0.0f,
//    };

    static const GLfloat positionData[] = {
            -1.0f,1.0f,1.0f, //adelante - 0
            1.0f,1.0f,1.0f,
            1.0f,-1.0f,1.0f,
            -1.0f,-1.0f,1.0f,
            -1.0f,1.0f,-1.0f, //atras - 4
            1.0f,1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,1.0f,1.0f, //izq - 8
            -1.0f,1.0f,-1.0f,
            -1.0f,-1.0f,1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,1.0f,1.0f, //der - 12
            1.0f,1.0f,-1.0f,
            1.0f,-1.0f,1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f, -1.0f, 1.0f, //abajo - 16
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, //arriba - 20
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
    };
    // Two UV coordinatesfor each vertex. They were created withe Blender.
    static const GLfloat g_uv_buffer_data[] = {
            0.000059f, 1.0f-0.000004f,
            0.000103f, 1.0f-0.336048f,
            0.335973f, 1.0f-0.335903f,
            1.000023f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.336024f, 1.0f-0.671877f,
            0.667969f, 1.0f-0.671889f,
            1.000023f, 1.0f-0.000013f,
            0.668104f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.000059f, 1.0f-0.000004f,
            0.335973f, 1.0f-0.335903f,
            0.336098f, 1.0f-0.000071f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.336024f, 1.0f-0.671877f,
            1.000004f, 1.0f-0.671847f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.668104f, 1.0f-0.000013f,
            0.335973f, 1.0f-0.335903f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.668104f, 1.0f-0.000013f,
            0.336098f, 1.0f-0.000071f,
            0.000103f, 1.0f-0.336048f,
            0.000004f, 1.0f-0.671870f,
            0.336024f, 1.0f-0.671877f,
            0.000103f, 1.0f-0.336048f,
            0.336024f, 1.0f-0.671877f,
            0.335973f, 1.0f-0.335903f,
            0.667969f, 1.0f-0.671889f,
            1.000004f, 1.0f-0.671847f,
            0.667979f, 1.0f-0.335851f
    };

    //create vbo
    glGenBuffers(1, &mesh->m_positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

    //create uv
    glGenBuffers(1, &mesh->m_uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

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

//    static const GLuint indices[] = {
//            0, 1, 2
//    };

    static const GLuint indices[] = {
        0, 3, 1, //adelante
        1, 3, 2,
        5, 7, 6, //atras
        6, 4, 5,
        8, 11, 10, //izq
        8, 9, 11,
        12, 14, 15, //der
        15, 13, 12,
        16, 17, 18, //abajo
        18, 19, 16,
        20, 23, 22, //arriba
        20, 22, 21
    };

    // create buffer for the indices
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

    mesh->m_indexCount = sizeof(indices) / sizeof(GLuint);
    mesh->m_indexBuffer = elementbuffer;

    glBindVertexArray(0); // Unbind our Vertex Array Object

    return mesh;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &m_positionBuffer);
    glDeleteBuffers(1, &m_indexBuffer);
    glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Mesh::use() {
    glBindVertexArray(m_vertexArrayID);
}

void Mesh::draw() {
    use();

//    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDrawElements(
            GL_TRIANGLES,      // mode
            m_indexCount,    // count
            GL_UNSIGNED_INT,   // type
            (void*)0           // element array buffer offset
    );
    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvbuffer);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size : U+V => 2
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

}
