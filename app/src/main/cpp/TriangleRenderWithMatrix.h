//
// Created by 任振铭 on 2024/8/18.
//

#ifndef OPENGLES_DOC_TRIANGLERENDER_H
#define OPENGLES_DOC_TRIANGLERENDER_H

#include "jni.h"
#include "header.h"
#include "NativeAssetsLoader.h"

class TriangleRenderWithMatrix {
private:
    GLuint program;
    NativeAssetsLoader *loader;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
public:
    TriangleRenderWithMatrix(JNIEnv *env, jobject asset);

    ~TriangleRenderWithMatrix();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_TRIANGLERENDER_H
