//
// Created by SANDSTORM04 on 8/20/16.
//

#include "ShaderProgram.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ShaderProgram::ShaderProgram() {
    m_valid = false;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_programId);
}

shared_ptr<ShaderProgram> ShaderProgram::loadProgram(string vertexFilePath, string fragmentFilePath) {

    // Read the Vertex Shader code from the file
    string vertexShaderCode;
    ifstream vertexShaderStream(vertexFilePath, ios::in);
    if (vertexShaderStream.is_open()) {
        std::string Line = "";
        while (getline(vertexShaderStream, Line))
            vertexShaderCode += "\n" + Line;
        vertexShaderStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexFilePath.c_str());
        getchar();
        return nullptr;
    }

    // Read the Fragment Shader code from the file
    string fragmentShaderCode;
    ifstream fragmentShaderStream(fragmentFilePath, ios::in);
    if (fragmentShaderStream.is_open()) {
        std::string Line = "";
        while (getline(fragmentShaderStream, Line))
            fragmentShaderCode += "\n" + Line;
        fragmentShaderStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragmentFilePath.c_str());
        getchar();
        return nullptr;
    }

    shared_ptr<ShaderProgram> shaderProgram(make_shared<ShaderProgram>());

    // Create the shaders
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertexFilePath.c_str());
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexSourcePointer , NULL);
    glCompileShader(vertexShaderId);

    // Check Vertex Shader
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        char vertexShaderErrorMessage[infoLogLength+1];
        memset(&vertexShaderErrorMessage[0], 0, (infoLogLength+1) * sizeof(char));
        glGetShaderInfoLog(vertexShaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        printf("%s\n", &vertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragmentFilePath.c_str());
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer , NULL);
    glCompileShader(fragmentShaderId);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        char fragmentShaderErrorMessage[infoLogLength+1];
        memset(&fragmentShaderErrorMessage[0], 0, (infoLogLength+1) * sizeof(char));
        glGetShaderInfoLog(fragmentShaderId, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        printf("%s\n", &fragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    shaderProgram->m_programId = glCreateProgram();
    glAttachShader(shaderProgram->m_programId, vertexShaderId);
    glAttachShader(shaderProgram->m_programId, fragmentShaderId);
    glLinkProgram(shaderProgram->m_programId);

    // Check the program
    glGetProgramiv(shaderProgram->m_programId, GL_LINK_STATUS, &result);
    glGetProgramiv(shaderProgram->m_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        char programErrorMessage[infoLogLength+1];
        memset(&programErrorMessage[0], 0, (infoLogLength+1) * sizeof(char));
        glGetProgramInfoLog(shaderProgram->m_programId, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    } else {
        shaderProgram->m_valid = true;
    }

    glDetachShader(shaderProgram->m_programId, vertexShaderId);
    glDetachShader(shaderProgram->m_programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return shaderProgram;
}

void ShaderProgram::use() {
    glUseProgram(m_programId);
}

void ShaderProgram::setVec4(string var, float x, float y, float z, float w) {
    GLint loc = glGetUniformLocation(m_programId, var.c_str());
    if (loc != -1)
    {
        glUniform4f(loc, x, y, z, w);
    }
}