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
#include <core/core/sdk/PerspectiveCamera.hpp>
#include <core/core/sdk/lights/DirectionalLight.hpp>
#include <core/core/sdk/lights/PointLight.hpp>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "SceneObject.hpp"
#include "Texture.hpp"


using namespace glm;


void RenderPass::execute() {

    initContext();
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    bool useDirectionalLight = false;

    shared_ptr<Mesh> mesh = Mesh::createBox();
    shared_ptr<Mesh> mesh2 = Mesh::createBox();
    shared_ptr<Mesh> mesh3 = Mesh::createBox();

    SceneObject meshObject;
    meshObject.m_transform->setPosition( -2.0f, 0.0f, 0.0f);
    meshObject.m_transform->setRotation( 0.0f, 0.0f, 0.0f);
    meshObject.m_transform->setScale( 1.0f, 1.0f, 1.0f);
    meshObject.m_transform->refreshTRS();

    SceneObject meshObject2;
    meshObject2.m_transform->setPosition( 2.0f, 0.0f, 0.0f);
    meshObject2.m_transform->setRotation( 1.0f, 1.0f, 1.0f);
    meshObject2.m_transform->setScale( 1.0f, 1.0f, 1.0f);
    meshObject2.m_transform->refreshTRS();

    SceneObject meshObject3;
    meshObject3.m_transform->setPosition( 2.0f, 0.0f, 0.0f);
    meshObject3.m_transform->setRotation( 0.0f, 0.0f, 0.0f);
    meshObject3.m_transform->setScale( 0.25f, 0.25f, 0.25f);
    meshObject3.m_transform->refreshTRS();

    SceneObject cameraObject;
    cameraObject.m_transform->setPosition( 0.0f, 0.0f, 10.0f);
    cameraObject.m_transform->setRotation( 0.0f, 0.0f, 0.0f);
    cameraObject.m_transform->setScale( 1.0f, 1.0f, 1.0f);
    cameraObject.m_transform->refreshTRS();

    SceneObject lightSceneObject;
    lightSceneObject.m_transform->setPosition( 0.0f, 0.0f, 0.0f);
    lightSceneObject.m_transform->setRotation( 0.0f, 3.14f, 0.0f);
    lightSceneObject.m_transform->setScale( 1.0f, 1.0f, 1.0f);
    lightSceneObject.m_transform->refreshTRS();

    //Create Texture
    shared_ptr<Texture> texture = Texture::loadBMP("grey_diffuse.bmp");
    shared_ptr<Texture> specularTexture = Texture::loadBMP("specular.bmp");
    shared_ptr<Texture> normalTexture = Texture::loadBMP("normal.bmp");

    // Cameras
    shared_ptr<SceneObject> sharedPtrSceneObject = make_shared<SceneObject>(cameraObject);
    weak_ptr<SceneObject> weakPtrSceneObject(sharedPtrSceneObject);

//    PerspectiveCamera* camera = new PerspectiveCamera(weakPtrSceneObject, 1.5f, 1.5f, 1.0f, 100.0f);
    OrthographicCamera* camera = new OrthographicCamera(weakPtrSceneObject, 8.0f, 8.0f, 1.0f, 100.0f);

    shared_ptr<ShaderProgram> shaderProgram;
    shared_ptr<SceneObject> sharedPtrLightOwner;
    LightComponent* light;
    DirectionalLight* directionalLight;
    PointLight* pointLight;
    if(useDirectionalLight){
        // Directional
        shaderProgram = ShaderProgram::loadProgram("VertexShader.vertexshader", "PhongDirectionalFragmentShader.fragmentshader");
        sharedPtrLightOwner = make_shared<SceneObject>(lightSceneObject);
        weak_ptr<SceneObject> weakPtrLightOwner(sharedPtrLightOwner);
        directionalLight = new DirectionalLight(weakPtrLightOwner);
    }else{
        // PointLight
        shaderProgram = ShaderProgram::loadProgram("VertexShader.vertexshader", "PhongPointLightFragmentShader.fragmentshader");
        sharedPtrLightOwner = make_shared<SceneObject>(meshObject3);
        weak_ptr<SceneObject> weakPtrLightOwner(sharedPtrLightOwner);
        pointLight = new PointLight(weakPtrLightOwner);
    }

    float mesh1Rotation = 0.0f;
    float lightTranslationCoef = 1.0f;
    float lightTranslation = -5.0f;

    do{
        glClearColor(1.0f, 0.0f, 0.0f ,1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        shaderProgram->use();

        // Set textures
        texture->bind(0);
        shaderProgram->setInt("u_texture", 0);
        specularTexture->bind(1);
        shaderProgram->setInt("u_specularMap", 1);
        normalTexture->bind(2);
        shaderProgram->setInt("u_normalMap", 2);

        // Set camera position
        float* cameraPosition = camera->getPosition();
        shaderProgram->setVec3("cameraPosition", cameraPosition[0], cameraPosition[1], cameraPosition[2]);

        // Rotate Mesh1
        meshObject.m_transform->setRotation( 0.0f, mesh1Rotation, 0.0f);
        meshObject.m_transform->refreshTRS();
        mesh1Rotation += 0.1/60;

        // Draw meshObject1
        Matrix4x4* m = meshObject.getPosition();
        Matrix4x4* v = camera->getViewMatrix();
        Matrix4x4* p = camera->getProjectionMatrix();
        Matrix4x4* aux = p->operator*(*v);
        aux = aux->operator*(*m);
        shaderProgram->setMat4("mvp", *aux);
        shaderProgram->setMat4("m", *m);
        mesh->draw();

        // Draw meshObject2
        Matrix4x4* m2 = meshObject2.getPosition();
        Matrix4x4* v2 = camera->getViewMatrix();
        Matrix4x4* p2 = camera->getProjectionMatrix();
        Matrix4x4* aux2 = p2->operator*(*v2);
        aux2 = aux2->operator*(*m2);
        shaderProgram->setMat4("mvp", *aux2);
        shaderProgram->setMat4("m", *m2);
        mesh2->draw();

        // Draw meshObject3
        meshObject3.m_transform->setPosition(lightTranslation, 0.0f, 5.0f);
        meshObject3.m_transform->refreshTRS();
        Matrix4x4* m3 = meshObject3.getPosition();
        Matrix4x4* v3 = camera->getViewMatrix();
        Matrix4x4* p3 = camera->getProjectionMatrix();
        Matrix4x4* aux3 = p3->operator*(*v3);
        aux3 = aux3->operator*(*m3);
        shaderProgram->setMat4("mvp", *aux3);
        shaderProgram->setMat4("m", *m3);
        mesh3->draw();

        if(useDirectionalLight){
            float* lightvec = directionalLight->getDirection();
            shaderProgram->setVec3("lightDirectional", lightvec[0], lightvec[1], lightvec[2]);
            //      Move PointLight
            meshObject3.m_transform->setPosition(lightTranslation, 0.0f, 8.0f);
            meshObject3.m_transform->refreshTRS();
        } else {
            float* lightPosition = pointLight->getPosition();
            shaderProgram->setVec3("lightPosition", lightPosition[0], lightPosition[1], lightPosition[2]);
            lightTranslation += (lightTranslationCoef*0.01f);
            if(lightTranslation > 5.0f){
                lightTranslationCoef = -1.0f;
            }
            if(lightTranslation < -5.0f){
                lightTranslationCoef = 1.0f;
            }
        }

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
