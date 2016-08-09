cmake_minimum_required(VERSION 3.5)
project(SimpleEngine)

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
        core/core/test/MatrixTest.cpp core/core/test/MatrixTest.hpp core/core/test/JsonTest.cpp core/core/test/JsonTest.hpp core/core/test/SceneObjectTest.cpp core/core/test/SceneObjectTest.hpp)

add_executable(SimpleEngine ${SOURCE_FILES})
#add_library(SimpleEngine ${SOURCE_FILES})
