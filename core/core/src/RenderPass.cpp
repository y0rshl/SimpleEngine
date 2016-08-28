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
#include <core/core/sdk/OrthographicCamera.hpp>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "SceneObject.hpp"
#include "Texture.hpp"


using namespace glm;


void RenderPass::execute() {

    initContext();

    shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    shared_ptr<Mesh> mesh = Mesh::createBox();

    SceneObject sceneObject;
    Matrix4x4 *trs;

    sceneObject.m_transform->setPosition( 1, 1, 1);
    sceneObject.m_transform->setRotation( 1, 0, 0);
    sceneObject.m_transform->setScale( 1, 1, 1);
    sceneObject.m_transform->setTRS(trs->makeTRS( 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));

    shared_ptr<SceneObject> sharedPtrSceneObject = make_shared<SceneObject>(sceneObject);
    weak_ptr<SceneObject> weakPtrSceneObject(sharedPtrSceneObject);
    OrthographicCamera* camera = new OrthographicCamera(weakPtrSceneObject, 0.5f, 0.5f, 1.0f, 1.0f);
    printf("Before Do while\n");

    //Create Texture
    shared_ptr<Texture> texture = Texture::loadBMP("uvtemplate.bmp");
    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(shaderProgram->getProgramId(), "u_texture");


    do{
        glClearColor(1.0f, 0, 0 ,1.0f);
        glClear( GL_COLOR_BUFFER_BIT );
        printf("Set up shader... ");
        // Use our shader
        shaderProgram->use();



        shaderProgram->setVec4("outColor", 1, 0, 1, 1);
        printf("Shader Ready!!!\nCreate MVP... ");
        // Define MVP matrixes
        Matrix4x4* m = sceneObject.getPosition();
        Matrix4x4* v = camera->getViewMatrix();
        Matrix4x4* p = camera->getProjectionMatrix();

        printf("MPV Created!!!\nMultiply Matrixes... ");
        // Multiply Matrixes
        Matrix4x4* aux = m->operator*(*v);
        aux = aux->operator*(*p);
        printf("Multipy ready!!!\nSet shader matrix... ");
        // Set matrix in shader Program
        shaderProgram->setMat4("mvp", *aux);
        printf("Shader Matrix ready!!!\n");



//        Matrix4x4 scale = Matrix4x4::makeScaleMatrix(0.5f, 0.5f, 0.5f);
//
//        shaderProgram->setMat4("mvp", scale);
//        shaderProgram->setVec4("outColor", 1, 1, 1, 1);
//
//        // Bind our texture in Texture Unit 0
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture->texture_id);
//        // Set our "myTextureSampler" sampler to user Texture Unit 0
//        glUniform1i(TextureID, 0);



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
