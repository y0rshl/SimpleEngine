//
// Created by Leonel Badi on 9/8/16.
//

#include <Matrix4x4.hpp>
#include "SceneObjectTest.hpp"

void SceneObjectTest::testSceneTree() {
    std::shared_ptr<SceneObject> father(new SceneObject());
    std::shared_ptr<SceneObject> child(new SceneObject());

    float fatherValues[4][4] = {
            {1,0,0,1},
            {0,1,0,2},
            {0,2,1,0},
            {0,0,0,1}
    };
    float childValues[4][4] = {
            {1,0,0,-1},
            {0,1,0,2},
            {0,0,1,2},
            {0,0,0,1}
    };
    Matrix4x4* trsFather = new Matrix4x4(fatherValues);
    Matrix4x4* trsChild = new Matrix4x4(childValues);

    father->m_transform = std::make_shared<Transform>(Transform(trsFather));
    child->m_transform = std::make_shared<Transform>(Transform(trsChild));
    child->parent = father;

    Matrix4x4* position = child->getPosition();
    Matrix4x4* fatherPosition = father->getPosition();

    auto vals = position->getValues();

    printf("Child TRS Values : \n");
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            printf(" %f ", vals[i][j]);
        }
        printf("\n");
    }

    vals = fatherPosition->getValues();
    printf("Father TRS Values : \n");
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            printf(" %f ", vals[i][j]);
        }
        printf("\n");
    }
}