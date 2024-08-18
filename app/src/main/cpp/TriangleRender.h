//
// Created by 任振铭 on 2024/8/18.
//

#ifndef OPENGLES_DOC_TRIANGLERENDER_H
#define OPENGLES_DOC_TRIANGLERENDER_H

#include "jni.h"
#include "header.h"
#include "NativeAssetsLoader.h"

class TriangleRender {
private:
    GLuint program;
    NativeAssetsLoader *loader;
public:
    TriangleRender(JNIEnv *env, jobject asset);

    ~TriangleRender();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_TRIANGLERENDER_H
