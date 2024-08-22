//
// Created by 任振铭 on 2024/8/21.
//

#ifndef OPENGLES_DOC_TEXTUREIMAGERENDER_H
#define OPENGLES_DOC_TEXTUREIMAGERENDER_H
#include "NativeAssetsLoader.h"
#include "header.h"
#include "GLUtils.h"

class TextureImageRender {
public:
    GLuint program;
    GLint positionLocation;
    GLint coordinateLocation;
    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;
    GLint textureLocation;
    GLuint texture;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    int image_width;
    int image_height;

    NativeAssetsLoader *loader;
    TextureImageRender(JNIEnv *env, jobject asset);

    ~TextureImageRender();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_TEXTUREIMAGERENDER_H
