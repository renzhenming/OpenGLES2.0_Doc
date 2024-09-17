//
// Created by 任振铭 on 2024/8/24.
//

#ifndef OPENGLES_DOC_CUBE_H
#define OPENGLES_DOC_CUBE_H

#include "../header.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"

class Cube {
public:
    GLint positionLocation;
    GLint colorLocation;
    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;

    GLuint program;
    NativeAssetsLoader *loader;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    static float cubePositions[];
    static short index[];
    static float color[];

    void translateRotateScale();

    Cube(JNIEnv *env, jobject asset);

    ~Cube();

    void create();

    void onChanged(int with, int height);

    void draw();
};


#endif //OPENGLES_DOC_CUBE_H
