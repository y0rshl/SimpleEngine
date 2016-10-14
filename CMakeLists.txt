cmake_minimum_required(VERSION 3.5)
project(SimpleEngine)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


# Compile external dependencies
add_subdirectory (external)

if(INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

#External directories
include_directories(
        external/AntTweakBar-1.16/include/
        external/glfw-3.1.2/include/GLFW/
        external/glm-0.9.7.1/
        external/glew-1.13.0/include/
        external/assimp-3.0.1270/include/
        external/bullet-2.81-rev2613/src/
        .
)
#Set ALL_LIBS VAR
set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130
        )
add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

include_directories(core/core/sdk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        core/core/src/core.cpp
        core/core/src/Matrix4x4.cpp
        core/core/src/Mesh.cpp
        core/core/src/Scene.cpp
        core/core/src/SceneObject.cpp
        core/core/src/Transform.cpp
        core/core/src/Vector4.cpp
        core/core/src/Engine.cpp
        core/core/src/shader.cpp
        core/core/test/MatrixTest.cpp core/core/test/MatrixTest.hpp core/core/test/JsonTest.cpp core/core/test/JsonTest.hpp core/core/test/SceneObjectTest.cpp core/core/test/SceneObjectTest.hpp core/core/src/Component.cpp core/core/sdk/Component.hpp core/core/src/RenderPass.cpp core/core/sdk/RenderPass.hpp core/core/src/MeshRendererComponent.cpp core/core/src/CameraComponent.cpp core/core/sdk/CameraComponent.hpp core/core/src/PerspectiveCamera.cpp core/core/sdk/PerspectiveCamera.hpp core/core/src/OrthographicCamera.cpp core/core/sdk/OrthographicCamera.hpp
        core/core/src/shaders/SimpleVertexShader.vertexshader
        core/core/src/shaders/SimpleFragmentShader.fragmentshader core/core/src/ShaderProgram.cpp core/core/src/ShaderProgram.hpp core/core/src/Texture.cpp core/core/sdk/Texture.hpp core/core/src/lights/LightComponent.cpp core/core/sdk/lights/LightComponent.hpp core/core/src/lights/DirectionalLight.cpp core/core/sdk/lights/DirectionalLight.hpp core/core/src/lights/PointLight.cpp core/core/sdk/lights/PointLight.hpp core/core/src/lights/SpotLight.cpp core/core/sdk/lights/SpotLight.hpp)


message(STATUS "Copy resources")
configure_file(core/core/src/shaders/VertexShader.vertexshader VertexShader.vertexshader COPYONLY)
configure_file(core/core/src/shaders/PhongDirectionalFragmentShader.fragmentshader PhongDirectionalFragmentShader.fragmentshader COPYONLY)
configure_file(core/core/src/shaders/PhongPointLightFragmentShader.fragmentshader PhongPointLightFragmentShader.fragmentshader COPYONLY)
configure_file(core/core/src/shaders/SimpleVertexShader.vertexshader SimpleVertexShader.vertexshader COPYONLY)
configure_file(core/core/src/shaders/SimpleFragmentShader.fragmentshader SimpleFragmentShader.fragmentshader COPYONLY)
configure_file(core/core/src/textures/uvtemplate.bmp uvtemplate.bmp COPYONLY)
configure_file(core/core/src/textures/diffuse.bmp diffuse.bmp COPYONLY)
configure_file(core/core/src/textures/grey_diffuse.bmp grey_diffuse.bmp COPYONLY)
configure_file(core/core/src/textures/specular.bmp specular.bmp COPYONLY)
configure_file(core/core/src/textures/normal.bmp normal.bmp COPYONLY)
configure_file(core/core/src/textures/brickwall.bmp brickwall.bmp COPYONLY)
configure_file(core/core/src/textures/brickwall_normal.bmp brickwall_normal.bmp COPYONLY)


add_executable(SimpleEngine ${SOURCE_FILES})
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(SimpleEngine ${ALL_LIBS})

#add_library(SimpleEngine ${SOURCE_FILES})
