//
// Created by 任振铭 on 2024/8/30.
//

#ifndef OPENGLES_DOC_FBORENDER_H
#define OPENGLES_DOC_FBORENDER_H

#include "../header.h"

class FboRender {
public:
    GLint loadedTextureId;
    int image_width;
    int image_height;
    GLint fbo_program;
    int fbo_positionHandle1;
    int fbo_textureCoordHandle1;
    int fbo_textureHandle1;
    GLuint frame_buffer;
    GLuint fbo_texture;

    GLint window_program;
    int window_positionHandle1;
    int window_textureCoordHandle1;
    int window_textureHandle1;

    FboRender(JNIEnv *env, jobject asset);

    ~FboRender();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();
};


#endif //OPENGLES_DOC_FBORENDER_H
