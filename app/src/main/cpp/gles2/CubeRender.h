//
// Created by 任振铭 on 2024/8/21.
//

#ifndef OPENGLES_DOC_CUBERENDER_H
#define OPENGLES_DOC_CUBERENDER_H
#include "../header.h"

class CubeRender {
private:
    GLuint program;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    int positionLocation;
    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;
    GLint colorLocation;
public:
    CubeRender(JNIEnv *env, jobject asset);

    ~CubeRender();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_CUBERENDER_H
