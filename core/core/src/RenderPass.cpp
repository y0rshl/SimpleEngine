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
#include <core/core/sdk/PointLight.hpp>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

#define pi 3.14

using namespace glm;

void RenderPass::execute() {

    initContext();
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    //shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
    shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "DirectionalFragmentShader.fragmentshader");
//    shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "PointLightFragmentShader.fragmentshader");

    shared_ptr<Mesh> mesh = Mesh::createBox();
    shared_ptr<Mesh> meshLight = Mesh::createBox();

    //Create Texture
    shared_ptr<Texture> texture = Texture::loadBMP("uvtemplate.bmp");
    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(shaderProgram->getProgramId(), "u_texture");

    //Mi codigo
    //Objeto
    shared_ptr<SceneObject> meshSceneObject = make_shared<SceneObject>();
    meshSceneObject->m_transform->set_position(0.0f, 0.0f, 0.0f);
    meshSceneObject->m_transform->set_rotation(pi/4, pi/3, 0.0f);
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
    shared_ptr<OrthographicCamera> oc = make_shared<OrthographicCamera>(8.0f,8.0f,20.0f,1.0f);
    camSceneObject->addComponent(static_pointer_cast<Component>(oc));

    //Luz
    shared_ptr<SceneObject> lightSceneObject = make_shared<SceneObject>();
    lightSceneObject->m_transform->set_position(2.0f, 2.0f, 10.0f);
    lightSceneObject->m_transform->set_rotation(0.0f, pi, 0.0f);
    lightSceneObject->m_transform->set_scale(0.5f,0.5f,1.0f);
    lightSceneObject->m_transform->refreshTRS();

    //Directional Light
    shared_ptr<DirectionalLight> dl = make_shared<DirectionalLight>(8.0f,8.0f,20.0f,1.0f);
    lightSceneObject->addComponent(static_pointer_cast<Component>(dl));

    //Point Light
 //   shared_ptr<PointLight> pl = make_shared<PointLight>();
 //   lightSceneObject->addComponent(static_pointer_cast<Component>(pl));

  //  float y = 0.0f;
    do{
        glClearColor(1.0f, 0, 0 ,1.0f);
        //glClear( GL_COLOR_BUFFER_BIT );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Use our shader
        shaderProgram->use();

        //mi codigo
        //MVP de la luz
        Matrix4x4* mL = meshSceneObject->getPosition();
        Matrix4x4* vL = dl->getViewMatrix();
        Matrix4x4* pL = dl->getProjectionMatrix();

        Matrix4x4* vmL = (*vL)*(*mL);
        Matrix4x4* pvmL = (*pL)*(*vmL);

      //  shaderProgram->setMat4("mvp", *pvmL);


        //MVP de la camara
        Matrix4x4* m = meshSceneObject->getPosition();
        Matrix4x4* v = oc->getViewMatrix();
        Matrix4x4* p = oc->getProjectionMatrix();

        //Direccion de la luz en directionalLight
        Vec4 dirLight = dl->getDirLight();

        //Posicion de la luz en pointLight
        //Vec4 lightPosition = pl->getPosition();
        //Posicion de la camara
        Vec4 camPosition = oc->getPosition();

        Matrix4x4* vm = (*v)*(*m);
        //Es column major por eso es pvm
        Matrix4x4* pvm = (*p)*(*vm);

        shaderProgram->setMat4("m", *m);
        shaderProgram->setMat4("mvp", *pvm);
        shaderProgram->setVec4("outColor", 1, 1, 1, 1);
        shaderProgram->setVec4("dirLight", dirLight.getValues()[0], dirLight.getValues()[1], dirLight.getValues()[2], dirLight.getValues()[3]);
     //   shaderProgram->setVec4("positionLight", lightPosition.getValues()[0], lightPosition.getValues()[1], lightPosition.getValues()[2], lightPosition.getValues()[3]);
        shaderProgram->setVec4("positionCam", camPosition.getValues()[0], camPosition.getValues()[1], camPosition.getValues()[2], camPosition.getValues()[3]);

        //Movimiento de la posicion para la pointLight
  //     lightSceneObject->m_transform->set_position(y, 0.0f, 10.0f);
  //     y += 0.01f;

        //Rotacion para la directionalLight
   //     lightSceneObject->m_transform->set_rotation(0.0f, y, 0.0f);
   //     y += pi/8;

/*        camSceneObject->m_transform->set_position(x, 0.0f, 0.0f);
        camSceneObject->m_transform->refreshTRS();
        x += -0.001f;*/

        //Rotacion del objeto
//        meshSceneObject->m_transform->set_rotation(pi/4, y, 0.0f);
//        meshSceneObject->m_transform->refreshTRS();
//        y+= 0.01f;

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

        //Agrego un mesh con la posicion de la luz
        Matrix4x4* m2 = lightSceneObject->getPosition();
        Matrix4x4* v2 = oc->getViewMatrix();
        Matrix4x4* p2 = oc->getProjectionMatrix();

        Matrix4x4* vm2 = (*v2)*(*m2);
        //Es column major por eso es pvm
        Matrix4x4* pvm2 = (*p2)*(*vm2);

        shaderProgram->setMat4("mvp", *pvm2);
        shaderProgram->setMat4("m", *m2);
        meshLight->draw();

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
    window = glfwCreateWindow( 768, 768, "Simple window", NULL, NULL);
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
