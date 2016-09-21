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
#include <core/core/sdk/DirectionalLight.hpp>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

using namespace glm;


void RenderPass::execute() {

    initContext();

    shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    shared_ptr<Mesh> mesh = Mesh::createBox();

    //Create Texture
    shared_ptr<Texture> texture = Texture::loadBMP("uvtemplate.bmp");
    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(shaderProgram->getProgramId(), "u_texture");

    //Mi codigo
    //Objeto
    shared_ptr<SceneObject> meshSceneObject = make_shared<SceneObject>();
    meshSceneObject->m_transform->set_position(0.0f, 0.0f, 0.0f);
    meshSceneObject->m_transform->set_rotation(0.0f, 0.0f, 0.0f);
    meshSceneObject->m_transform->set_scale(1.0f,1.0f,1.0f);
    meshSceneObject->m_transform->refreshTRS();

    //Camara
    shared_ptr<SceneObject> camSceneObject = make_shared<SceneObject>();
    camSceneObject->m_transform->set_position(0.0f, 0.0f, 10.0f);
    camSceneObject->m_transform->set_rotation(0.0f, 0.0f, 0.0f);
    camSceneObject->m_transform->set_scale(1.0f,1.0f,1.0f);
    camSceneObject->m_transform->refreshTRS();

  //  shared_ptr<PerspectiveCamera> pc = make_shared<PerspectiveCamera>(1.0f,1.0f,1.0f,10.0f);
  //  camSceneObject->addComponent(static_pointer_cast<Component>(pc));
    shared_ptr<OrthographicCamera> oc = make_shared<OrthographicCamera>(8.0f,8.0f,1.0f,10.0f);
    camSceneObject->addComponent(static_pointer_cast<Component>(oc));

    //Luz
    shared_ptr<SceneObject> lightSceneObject = make_shared<SceneObject>();
    lightSceneObject->m_transform->set_position(0.0f, 0.0f, 10.0f);
    lightSceneObject->m_transform->set_rotation(0.0f, 0.0f, 0.0f);
    lightSceneObject->m_transform->set_scale(1.0f,1.0f,1.0f);
    lightSceneObject->m_transform->refreshTRS();

    shared_ptr<DirectionalLight> dl = make_shared<DirectionalLight>();
    lightSceneObject->addComponent(static_pointer_cast<Component>(dl));

    float rx = 0.1f;
    do{
        glClearColor(1.0f, 0, 0 ,1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        shaderProgram->use();

        //mi codigo
        Matrix4x4* m = meshSceneObject->getPosition();
        Matrix4x4* v = oc->getViewMatrix();
        Matrix4x4* p = oc->getProjectionMatrix();

        Vec4 dirLight = dl->getDirLight();

        Matrix4x4* vm = (*v)*(*m);
        //Es column major por eso es pvm
        Matrix4x4* pvm = (*p)*(*vm);

        shaderProgram->setMat4("m", *m);
        shaderProgram->setMat4("mvp", *pvm);
        shaderProgram->setVec4("outColor", 1, 1, 1, 1);
        shaderProgram->setVec4("dirLight", dirLight.getValues()[0], dirLight.getValues()[1], dirLight.getValues()[2], dirLight.getValues()[3]);
        //Le paso la normal de cada vertice para calcular la intesidad de la luz
        //TODO normalizar cada vertice con norma2
        shaderProgram->setVec4("normal", 0,0,-1,0);

/*        camSceneObject->m_transform->set_rotation(rx, 0.0f, 0.0f);
        camSceneObject->m_transform->refreshTRS();
        rx += 0.001f;*/

        //Su codigo
//        Matrix4x4 scale = Matrix4x4::makeScaleMatrix(0.5f, 0.5f, 0.5f);
//        shaderProgram->setMat4("mvp", scale);
//        shaderProgram->setVec4("outColor", 1, 1, 1, 1);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->texture_id);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

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
