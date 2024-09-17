//
// Created by 任振铭 on 2024/8/21.
//

#ifndef OPENGLES_DOC_TEXTUREIMAGERENDER_H
#define OPENGLES_DOC_TEXTUREIMAGERENDER_H

#include "NativeAssetsLoader.h"
#include "header.h"
#include "GLUtils.h"

static inline void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "after %s() glError (0x%x)\n", op, error);
    }
}

class AbsGlRender {
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

    virtual GLuint CreateTexture() = 0;

    virtual void InitShader();

    ~AbsGlRender();

    void CreateSurface(unsigned char *vs_code, unsigned char *fs_code);

    void SurfaceChanged(int with, int height);

    virtual void ConfigMatrix(int width, int height);

    void DrawFrame();

    virtual void Clear();

    virtual void ClearColor();

    virtual void UseProgram();

    virtual void SetExpandData();

    virtual void BindTexture();

    virtual void Draw();
};


#endif //OPENGLES_DOC_TEXTUREIMAGERENDER_H
