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
#define orthographic 1
#define perspective 2

//Tamaño de la textura
const GLuint SHADOW_WIDTH = 768, SHADOW_HEIGHT = 768;

using namespace glm;

void RenderPass::execute() {

    initContext();
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    //shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
    shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "DirectionalFragmentShader.fragmentshader");
    shared_ptr<ShaderProgram> depthShader = ShaderProgram::loadProgram("DepthVertexShader.vertexshader", "LightMapFragmentShader.fragmentshader");
//    shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::loadProgram("SimpleVertexShader.vertexshader", "PointLightFragmentShader.fragmentshader");

    shared_ptr<Mesh> mesh = Mesh::createBox();
    shared_ptr<Mesh> mesh2 = Mesh::createBox();
    shared_ptr<Mesh> mesh3 = Mesh::createBox();
    shared_ptr<Mesh> floor = Mesh::createBox();

    //Create Texture
    shared_ptr<Texture> texture = Texture::loadBMP("trestraou2_Base_Color.bmp");
    //TODO encontrar una textura especular correcta
    shared_ptr<Texture> textureSpec = Texture::loadBMP("trestraou2_Base_Color.bmp");
    shared_ptr<Texture> textureNormal = Texture::loadBMP("trestraou2_Normal.bmp");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(shaderProgram->getProgramId(), "u_texture");

    //GENERATE a depth map
    //create a framebuffer object for rendering the depth map
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    GLuint depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //Objeto
    shared_ptr<SceneObject> meshSceneObject = make_shared<SceneObject>();
    createSceneObject(meshSceneObject, -2.0f, 0.0f, 0.0f, pi/4, pi/3, 0.0f, 1.0f,1.0f,1.0f);

    shared_ptr<SceneObject> meshSceneObject2 = make_shared<SceneObject>();
    createSceneObject(meshSceneObject2, 2.0f, 2.0f, 1.0f, pi/6, pi/6, 0.0f, 0.5f, 0.5f, 0.5f);

    shared_ptr<SceneObject> meshSceneObject3 = make_shared<SceneObject>();
    createSceneObject(meshSceneObject3, 0.5f, -2.0f, -1.0f, pi/3, pi/6, 0.0f, 0.25f, 0.5f, 0.5f);

    //PARED
    shared_ptr<SceneObject> floorSceneObject = make_shared<SceneObject>();
    createSceneObject(floorSceneObject, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 4.0f, 4.0f, 2.0f);

    //Camara
    shared_ptr<SceneObject> camSceneObject = make_shared<SceneObject>();
    createSceneObject(camSceneObject, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f,1.0f,1.0f);

    shared_ptr<Camera> cam = setCamera(camSceneObject, orthographic, 8.0f, 8.0f, 1.0f, 50.0f);
   // shared_ptr<Camera> cam = setCamera(camSceneObject, perspective, 1.0f,1.0f,1.0f,10.0f);

    //Luz
    shared_ptr<SceneObject> lightSceneObject = make_shared<SceneObject>();
    createSceneObject(lightSceneObject, 0.0f, -5.0f, 1.0f, -pi/8, 0.0f, 0.0f, 1.0f,1.0f,1.0f);

    //Directional Light
    shared_ptr<DirectionalLight> dl = make_shared<DirectionalLight>(8.0f,8.0f,8.0f,1.0f);
    lightSceneObject->addComponent(static_pointer_cast<Component>(dl));

    //Point Light
 //   shared_ptr<PointLight> pl = make_shared<PointLight>();
 //   lightSceneObject->addComponent(static_pointer_cast<Component>(pl));

    //---------------------------------

    do{
        glClearColor(1.0f, 1.0f, 1.0f ,1.0f); //el fondo que nunca dibujaste, va en blanco para que sea un shadow map
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //mi codigo

        // 1. first render to depth map
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        depthShader->use();
        //MVP de la luz
        Matrix4x4* pvmL = getMVPLight(meshSceneObject, lightSceneObject, dl);
        setMVPLight(depthShader , mesh , pvmL);

        //Draw mesh2
        Matrix4x4* pvmL2 = getMVPLight(meshSceneObject2, lightSceneObject, dl);
        setMVPLight(depthShader , mesh2 , pvmL2);

        //Draw mesh3
        Matrix4x4* pvmL3 = getMVPLight(meshSceneObject3, lightSceneObject, dl);
        setMVPLight(depthShader , mesh3 , pvmL3);

        //Draw floor
        Matrix4x4* pvmLF = getMVPLight(floorSceneObject, lightSceneObject, dl);
        setMVPLight(depthShader , floor , pvmLF);

        glBindFramebuffer(GL_FRAMEBUFFER, 0); //cambie el frameBuffer a la pantalla
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //muevo la camara
        moveCamera(camSceneObject.get(), 0.05f);

        //MVP de la camara
        Matrix4x4* m = meshSceneObject->getPosition();
        Matrix4x4* pvm = getMVPCamera(meshSceneObject, camSceneObject, cam);

        //Direccion de la luz en directionalLight
        Vec4 dirLight = dl->getDirLight();

        //Posicion de la luz en pointLight
        //Vec4 lightPosition = pl->getPosition();
        //Posicion de la camara
        Vec4 camPosition = cam->getPosition();

        // Use our shader
        shaderProgram->use();

        shaderProgram->setMat4("m", *m);
        shaderProgram->setMat4("mvp", *pvm);
        shaderProgram->setMat4("mvpLight", *pvmL);
        shaderProgram->setVec4("outColor", 1, 1, 1, 1);
        shaderProgram->setVec4("dirLight", dirLight.getValues()[0], dirLight.getValues()[1], dirLight.getValues()[2], dirLight.getValues()[3]);
     //   shaderProgram->setVec4("positionLight", lightPosition.getValues()[0], lightPosition.getValues()[1], lightPosition.getValues()[2], lightPosition.getValues()[3]);
        shaderProgram->setVec4("positionCam", camPosition.getValues()[0], camPosition.getValues()[1], camPosition.getValues()[2], camPosition.getValues()[3]);


        //Set texture
        texture->bind(0);
        shaderProgram->setInt("u_texture", 0);
        textureSpec->bind(1);
        shaderProgram->setInt("u_mapSpecular",1);
        textureNormal->bind(2);
        shaderProgram->setInt("u_mapNormal",2);

        //Bind del depthMap
        glActiveTexture(GL_TEXTURE0 + 3);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        shaderProgram->setInt("u_textureShadow",3);

        mesh->draw();

        //Draw mesh2
        drawMesh(shaderProgram, mesh2, pvmL2, meshSceneObject2, camSceneObject, cam);

        //Draw mesh3
        drawMesh(shaderProgram, mesh3, pvmL3, meshSceneObject3, camSceneObject, cam);

        //Draw floor
        drawMesh(shaderProgram, floor, pvmLF, floorSceneObject, camSceneObject, cam);

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

void RenderPass::setMVPLight (shared_ptr<ShaderProgram> &depthShader , shared_ptr<Mesh> mesh , Matrix4x4 *pvmL) {
    depthShader->setMat4("mvp", *pvmL);
    mesh->draw();
}

void RenderPass::drawMesh (shared_ptr<ShaderProgram> &shaderProgram , shared_ptr<Mesh> mesh , Matrix4x4 *mvpL ,
                           shared_ptr<SceneObject> &meshSceneObject , shared_ptr<SceneObject> &camSceneObject ,
                           shared_ptr<Camera> &cam) {
    Matrix4x4* pvm2 = getMVPCamera(meshSceneObject, camSceneObject, cam);
    Matrix4x4* m2 = meshSceneObject->getPosition();
    shaderProgram->setMat4("m", *m2);
    shaderProgram->setMat4("mvp", *pvm2);
    shaderProgram->setMat4("mvpLight", *mvpL);
    mesh->draw();
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


void RenderPass::createSceneObject (const shared_ptr<SceneObject> &meshSceneObject,
                                    float x, float y, float z,
                                    float rx, float ry, float rz,
                                    float sx, float sy, float sz) {
    meshSceneObject->m_transform->set_position(x, y, z);
    meshSceneObject->m_transform->set_rotation(rx, ry, rz);
    meshSceneObject->m_transform->set_scale(sx,sy,sz);
    meshSceneObject->m_transform->refreshTRS();
}

Matrix4x4 *RenderPass::getMVPLight (shared_ptr<SceneObject> &meshSceneObject , shared_ptr<SceneObject> &lightSceneObject ,
                               shared_ptr<DirectionalLight> &dl) {
    Matrix4x4* m = meshSceneObject->getPosition();
    Matrix4x4* v = lightSceneObject->getViewMatrix();
    Matrix4x4* p = dl->getProjectionMatrix();

    Matrix4x4* vm = (*v)*(*m);
    Matrix4x4* pvm = (*p)*(*vm);
    return pvm;
}

Matrix4x4 *RenderPass::getMVPCamera (shared_ptr<SceneObject> &meshSceneObject , shared_ptr<SceneObject> &camSceneObject ,
                               shared_ptr<Camera> &cam) {
    Matrix4x4* m = meshSceneObject->getPosition();
    Matrix4x4* v = camSceneObject->getViewMatrix();
    Matrix4x4* p = cam->getProjectionMatrix();

    Matrix4x4* vm = (*v)*(*m);
    Matrix4x4* pvm = (*p)*(*vm);
    return pvm;
}

shared_ptr<Camera> RenderPass::setCamera (shared_ptr<SceneObject> camSceneObject , int camera,
                                          float width, float height, float far, float near) {
    shared_ptr<Camera> cam;
    if(camera == orthographic){
        cam = make_shared<OrthographicCamera>(width, height, near, far);
        camSceneObject->addComponent(static_pointer_cast<Component>(cam));
    }else if(camera == perspective){
        cam = make_shared<PerspectiveCamera>(width,height,near,far);
        camSceneObject->addComponent(static_pointer_cast<Component>(cam));
    }
    return cam;


}

void RenderPass::moveCamera (SceneObject* so , float step) {

    bool move = false;
    Vec4 position = so->m_transform->get_position();
    Vec4 rotation = so->m_transform->get_rotation();

    float x = position.getX();
    float y = position.getY();
    float z = position.getZ();
    float rx = rotation.getX();
    float ry = rotation.getY();
    float rz = rotation.getZ();

    //mover a la izquierda la camara
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        x = x - step;
        move = true;
    }

    //mover a la derecha la camara
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        x = x + step;
        move = true;
    }

    //mover hacia arriba la camara
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        y = y + step;
        move = true;
    }

    //mover hacia abajo la camara
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        y = y - step;
        move = true;
    }

    //alejar la camara
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        z = z - step;
        move = true;
    }

    //acercar la camara
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        z = z + step;
        move = true;
    }

    //rotar la camara hacia la izquierda
/*    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        rx = rx - step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        rx = rx + step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        rx = ry - step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        rx = ry + step;
        move = true;
    }*/

    if(move){
        so->m_transform->set_position(x, y, z);
       // so->m_transform->set_rotation(rx,ry,rz);
        so->m_transform->refreshTRS();
    }



}

