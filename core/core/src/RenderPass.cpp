//
// Created by SANDSTORM04 on 8/18/16.
//

#include "RenderPass.hpp"
//#include <opengl/gl.h>
#include <stdio.h>

// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <glfw3.h>
GLFWwindow* window;
// Include GLM
#include <glm/glm.hpp>
// Include shader library
#include "shader.hpp"
#include <memory>
#include <core/core/sdk/SceneObject.hpp>
#include <core/core/sdk/Camera.h>
#include <core/core/sdk/PerspectiveCamera.hpp>
#include <core/core/sdk/OrthographicCamera.hpp>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

using namespace glm;


void RenderPass::execute() {

    initContext();

    shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    shared_ptr<Mesh> mesh = Mesh::createBox();

    //no se como llamar al metodo estatico de una sin crear la instancia
    Matrix4x4 *trs;

    SceneObject myso;
    myso.m_transform->set_position(0.0f, 0.0f, 0.0f);
    myso.m_transform->set_rotation(0.0f, 0.0f, 0.0f);
    myso.m_transform->set_scale(1.0f,1.0f,1.0f);
    myso.m_transform->set_TRS(trs->makeTRSMatrix( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));


    do{
        glClearColor(1.0f, 0, 0 ,1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        shaderProgram->use();

        PerspectiveCamera* pc = new PerspectiveCamera(1.0f,0.5f,0.5f,1.0f);
        //OrthographicCamera* oc = new OrthographicCamera(2,2,0.5f,3);

        pc->setSO(myso);

        Matrix4x4* m = myso.getPosition();
/*        Matrix4x4* v = pc->getViewMatrix();
        Matrix4x4* p = pc->getProjectionMatrix();

        Matrix4x4* mv = m->operator*(*v);
        Matrix4x4* mvp = mv->operator*(*p);*/

        //Matrix4x4 scale = Matrix4x4::makeScaleMatrix(0.5f, 0.5f, 0.5f);

        //shaderProgram->setMat4("mvp", *mvp);
        shaderProgram->setMat4("mvp", *m);
        shaderProgram->setVec4("outColor", 1, 1, 1, 1);

        mesh->draw();

//        // Draw the triangle !
//        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
//    glDeleteBuffers(1, &vertexbuffer);
//    glDeleteVertexArrays(1, &vertexArrayID);
//    glDeleteProgram(programId);
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return;
}

void RenderPass::initContext(){
    // Initialise GLFW
    glewExperimental = GL_TRUE;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Simple window", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return ;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void RenderPass::setViewport(int viewportX, int viewportY, int viewportWidth, int viewportHeight) {
    this->viewportX = viewportX;
    this->viewportY = viewportY;
    this->viewportWidth = viewportWidth;
    this->viewportHeight = viewportHeight;
}
