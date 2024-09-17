//
// Created by 任振铭 on 2024/8/24.
//

#ifndef OPENGLES_DOC_BLURTEXTUREIMAGERENDER_H
#define OPENGLES_DOC_BLURTEXTUREIMAGERENDER_H

#include "header.h"
#include "GLUtils.h"
#include "NativeAssetsLoader.h"
class YUV420Render {
public:
    GLuint program;
    GLint positionLocation;
    GLint coordinateLocation;
    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;
    GLint textureYLocation;
    GLint textureULocation;
    GLint textureVLocation;
    GLuint textureY;
    GLuint textureU;
    GLuint textureV;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    int image_width;
    int image_height;

    NativeAssetsLoader *loader;

    YUV420Render(JNIEnv *env, jobject asset);

    ~YUV420Render();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_BLURTEXTUREIMAGERENDER_H
