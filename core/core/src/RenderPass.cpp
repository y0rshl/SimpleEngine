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
#include "Mesh.hpp"
#include "SceneObject.hpp"
#include "Texture.hpp"


using namespace glm;


void RenderPass::execute() {

    initContext();
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    // Use directional light or Point Light
    bool useDirectionalLight = false;

    shared_ptr<Mesh> mesh = Mesh::createBox();
    shared_ptr<Mesh> mesh2 = Mesh::createBox();
    shared_ptr<Mesh> mesh3 = Mesh::createBox();
    shared_ptr<Mesh> mesh4 = Mesh::createBox();

    SceneObject meshObject;
    placeSceneObject(&meshObject, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    SceneObject meshObject2;
    placeSceneObject(&meshObject2, 2.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    SceneObject meshObject3;
    placeSceneObject(&meshObject3, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.25f, 0.25f);

    SceneObject cameraObject;
    placeSceneObject(&cameraObject, 0.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    SceneObject lightSceneObject;
    placeSceneObject(&lightSceneObject, 0.0f, 0.0f, 0.0f, 0.0f, 3.14f, 0.0f, 1.0f, 1.0f, 1.0f);

    SceneObject floorObject;
    placeSceneObject(&floorObject, 0.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f, 10.0f);

    //Create Texture
    shared_ptr<Texture> texture = Texture::loadBMP("grey_diffuse.bmp");
    shared_ptr<Texture> specularTexture = Texture::loadBMP("specular.bmp");
    shared_ptr<Texture> normalTexture = Texture::loadBMP("normal.bmp");

    // Cameras
    shared_ptr<SceneObject> sharedPtrSceneObject = make_shared<SceneObject>(cameraObject);
    weak_ptr<SceneObject> weakPtrSceneObject(sharedPtrSceneObject);

    PerspectiveCamera* camera = new PerspectiveCamera(weakPtrSceneObject, 60.0f, 60.0f, 0.1f, 100.0f);
//    OrthographicCamera* camera = new OrthographicCamera(weakPtrSceneObject, 8.0f, 8.0f, 1.0f, 100.0f);

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
    float movement = 0.5f;

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

        // Move camera
        moveCamera(camera, &cameraObject);

        // Set camera position
        float* cameraPosition = camera->getPosition();
        shaderProgram->setVec3("cameraPosition", cameraPosition[0], cameraPosition[1], cameraPosition[2]);

        // Rotate Mesh1
        meshObject.m_transform->setRotation( 0.0f, mesh1Rotation, 0.0f);
        meshObject.m_transform->refreshTRS();
        mesh1Rotation += 0.1/60;

        // Draw meshObject1
        drawMesh(mesh, &meshObject, camera, shaderProgram);

        // Draw meshObject2
        drawMesh(mesh2, &meshObject2, camera, shaderProgram);

        // Draw meshObject3
        lightTranslation += (lightTranslationCoef*0.01f);
        if(lightTranslation > 5.0f){
            lightTranslationCoef = -1.0f;
        }
        if(lightTranslation < -5.0f){
            lightTranslationCoef = 1.0f;
        }
        meshObject3.m_transform->setPosition(lightTranslation, 0.0f, 5.0f);
        meshObject3.m_transform->refreshTRS();
        drawMesh(mesh3, &meshObject3, camera, shaderProgram);

        // Draw floor
        drawMesh(mesh4, &floorObject, camera, shaderProgram);

        if(useDirectionalLight){
            float* lightvec = directionalLight->getDirection();
            shaderProgram->setVec3("lightDirectional", lightvec[0], lightvec[1], lightvec[2]);
        } else {
            float* lightPosition = pointLight->getPosition();
            shaderProgram->setVec3("lightPosition", lightPosition[0], lightPosition[1], lightPosition[2]);
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


void RenderPass::placeSceneObject(SceneObject* sceneObject, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz){
    sceneObject->m_transform->setPosition( x, y, z);
    sceneObject->m_transform->setRotation( rx, ry, rz);
    sceneObject->m_transform->setScale( sx, sy, sz);
    sceneObject->m_transform->refreshTRS();
};

void RenderPass::drawMesh(shared_ptr<Mesh> mesh, SceneObject* sceneObject, CameraComponent* camera, shared_ptr<ShaderProgram> shaderProgram){
    Matrix4x4* m = sceneObject->getPosition();
    Matrix4x4* v = camera->getViewMatrix();
    Matrix4x4* p = camera->getProjectionMatrix();
    Matrix4x4* aux = p->operator*(*v);
    aux = aux->operator*(*m);
    shaderProgram->setMat4("mvp", *aux);
    shaderProgram->setMat4("m", *m);
    mesh->draw();
};

void RenderPass::moveCamera(CameraComponent* camera, SceneObject* sceneObject){
    float step = 0.05f;
    float leftX = 0.0f;
    float rightX = 0.0f;
    float forwardZ = 0.0f;
    float backwardsZ = 0.0f;
    float upY = 0.0f;
    float downY = 0.0f;

    bool move = false;

    if(glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
        leftX = step;
        move = true;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
        rightX = step;
        move = true;
    }
    if(glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
        forwardZ = step;
        move = true;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
        backwardsZ = step;
        move = true;
    }
    if(glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        upY = step;
        move = true;
    }
    if(glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        downY = step;
        move = true;
    }

    if(move){
        float* cameraPosition = camera->getPosition();
        sceneObject->m_transform->setPosition(cameraPosition[0]+rightX-leftX, cameraPosition[1]+upY - downY, cameraPosition[2]-forwardZ+backwardsZ);
        sceneObject->m_transform->refreshTRS();
    }
};

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
