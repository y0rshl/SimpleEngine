cmake_minimum_required(VERSION 3.5)
project(SimpleEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    core/core/core.cpp
    core/core/core.hpp
    core/core/corePriv.hpp
    core/core/Matrix4x4.cpp
    core/core/Matrix4x4.hpp
    core/core/Mesh.cpp
    core/core/Mesh.hpp
    core/core/Scene.cpp
    core/core/Scene.hpp
    core/core/SceneObject.cpp
    core/core/SceneObject.hpp
    core/core/Transform.cpp
    core/core/Transform.hpp
    core/core/Vector4.cpp
    core/core/Vector4.hpp
    osx/osx/AppDelegate.h
    osx/osx/GameViewController.h
    osx/osx/OpenGLView.h
    osx/osx/SharedStructures.h)

add_executable(SimpleEngine ${SOURCE_FILES})