//
// Created by 任振铭 on 2024/8/23.
//

#ifndef OPENGLES_DOC_COOLTEXTUREIMAGERENDER_H
#define OPENGLES_DOC_COOLTEXTUREIMAGERENDER_H

#include "../header.h"
#include "GLUtils.h"
#include "NativeAssetsLoader.h"
class CoolTextureImageRender {
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

    CoolTextureImageRender(JNIEnv *env, jobject asset);

    ~CoolTextureImageRender();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_COOLTEXTUREIMAGERENDER_H
