//
// Created by SANDSTORM04 on 8/20/16.
//

#ifndef SIMPLEENGINE_SHADERPROGRAM_HPP
#define SIMPLEENGINE_SHADERPROGRAM_HPP


#include <string>
#include <memory>
#include <opengl/gl.h>

using namespace std;

class ShaderProgram {

public:
    static shared_ptr<ShaderProgram> loadProgram(string vertexFilePath, string fragmentFilePath);

    ShaderProgram();
    ~ShaderProgram();

    bool isValid() {return m_valid;}

    void use();

    void setVec4(string var, float x, float y, float z, float w);
private:
    bool m_valid;
//    GLuint m_vertexShaderId;
//    GLuint m_fragmentShaderId;
    GLuint m_programId;
};


#endif //SIMPLEENGINE_SHADERPROGRAM_HPP
