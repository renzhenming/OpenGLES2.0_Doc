//
// Created by 任振铭 on 2024/8/18.
//

#ifndef OPENGLES_DOC_TRIANGLERENDER_H
#define OPENGLES_DOC_TRIANGLERENDER_H

#include "jni.h"
#include "header.h"
#include "NativeAssetsLoader.h"

class TriangleRenderVBO_EBO {
private:
    GLuint program;
    NativeAssetsLoader *loader;
    int positionLocation;
    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;
    GLint colorLocation;
    glm::mat4 modelMatrix;
    glm::mat4 modelMatrix2;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    GLuint vbo;
    GLuint ebo;
public:
    TriangleRenderVBO_EBO(JNIEnv *env, jobject asset);

    ~TriangleRenderVBO_EBO();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_TRIANGLERENDER_H
