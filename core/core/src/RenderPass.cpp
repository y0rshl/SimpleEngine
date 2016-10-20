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
    bool useDirectionalLight = true;
    float mesh1Rotation = 0.0f;
    float lightTranslationCoef = 1.0f;
    float lightTranslation = -5.0f;

    shared_ptr<ShaderProgram> shadowShaderProgram;
    shadowShaderProgram = ShaderProgram::loadProgram("SimpleDepthVertexShader.vertexshader", "SimpleDepthFragmentShader.fragmentshader");

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
    placeSceneObject(&lightSceneObject, 0.0f, 0.0f, 1000.0f, 0.0f, 3.14f, 0.0f, 1.0f, 1.0f, 1.0f);

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

    // Light Camera for Shadow Mapping
    shared_ptr<SceneObject> sharedPtrLightSceneObject = make_shared<SceneObject>(lightSceneObject);
    weak_ptr<SceneObject> weakPtrLightSceneObject(sharedPtrLightSceneObject);
    OrthographicCamera* lightCamera = new OrthographicCamera(weakPtrLightSceneObject, 8.0f, 8.0f, 1.0f, 100.0f);

    // Depth Buffer
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
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
    float moveMeshes = true;
    do{
        // 1. Render to depht Map from light point of view
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        shadowShaderProgram->setInt("u_texture", 0);

        // Draw meshes
        drawMesh(mesh, &meshObject, lightCamera, shadowShaderProgram);
        drawMesh(mesh2, &meshObject2, lightCamera, shadowShaderProgram);
        drawMesh(mesh3, &meshObject3, lightCamera, shadowShaderProgram);
        drawMesh(mesh4, &floorObject, lightCamera, shadowShaderProgram);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. Render from camera
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        if(glfwGetKey(window, GLFW_KEY_P ) == GLFW_PRESS){
            moveMeshes = !moveMeshes;
        }

        glClearColor(0.5f, 0.8f, 0.98f ,1.0f);
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
        if(moveMeshes){
            meshObject.m_transform->setRotation( 0.0f, mesh1Rotation, 0.0f);
            meshObject.m_transform->refreshTRS();
            mesh1Rotation += 0.1/60;
        }

        // Draw meshObject1
        drawMesh(mesh, &meshObject, camera, shaderProgram);

        // Draw meshObject2
        drawMesh(mesh2, &meshObject2, camera, shaderProgram);

        // Draw meshObject3
        if(moveMeshes){
            lightTranslation += (lightTranslationCoef*0.01f);
            if(lightTranslation > 5.0f){
                lightTranslationCoef = -1.0f;
            }
            if(lightTranslation < -5.0f){
                lightTranslationCoef = 1.0f;
            }
            meshObject3.m_transform->setPosition(lightTranslation, 0.0f, 5.0f);
            meshObject3.m_transform->refreshTRS();
        }
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

    float rx = 0.0f;
    float ry = 0.0f;
    float rz = 0.0f;

    float forward = false;
    float backward = false;
    float left = false;
    float right = false;
    bool move = false;

    if(glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
        left = true;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
        right = true;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
        forward = true;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
        backward = true;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_Q ) == GLFW_PRESS){
        rx += step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        rx -= step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        ry += step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        ry -= step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_Z ) == GLFW_PRESS){
        rz += step;
        move = true;
    }

    if(glfwGetKey(window, GLFW_KEY_X ) == GLFW_PRESS){
        rz -= step;
        move = true;
    }

    if(move){
        float* cameraPosition = camera->getPosition();
        float* cameraDirection = camera->getDirection();
        float* cameraHorizontalDirection = camera->getHorizontalDirection();
        float* cameraRotation = camera->getRotation();
        
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        if(forward){
            x -= cameraDirection[0]*step;
            y -= cameraDirection[1]*step;
            z -= cameraDirection[2]*step;
        }

        if(backward){
            x += cameraDirection[0]*step;
            y += cameraDirection[1]*step;
            z += cameraDirection[2]*step;
        }

        if(left){
            x -= cameraHorizontalDirection[0]*step;
            y -= cameraHorizontalDirection[1]*step;
            z -= cameraHorizontalDirection[2]*step;
        }

        if(right){
            x += cameraHorizontalDirection[0]*step;
            y += cameraHorizontalDirection[1]*step;
            z += cameraHorizontalDirection[2]*step;
        }

        sceneObject->m_transform->setPosition(cameraPosition[0] + x,
                                              cameraPosition[1] + y,
                                              cameraPosition[2] + z);

        sceneObject->m_transform->setRotation(cameraRotation[0] + rx,
                                              cameraRotation[1] + ry,
                                              cameraRotation[2] + rz);

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
