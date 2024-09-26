//
// Created by 任振铭 on 2024/9/25.
//

#ifndef OPENGLES_DOC_GLFBORENDER_H
#define OPENGLES_DOC_GLFBORENDER_H

#include "GLBaseRender.h"

class GLFboRender : public GLBaseRender {

public:
    GLuint fbo;
    GLuint vao[2];
    GLuint texture;
    GLuint fbo_texture;
    GLuint mFboProgram;
    GLint mTextureLocation;
    GLint mFboTextureLocation;

    GLFboRender();

    virtual ~GLFboRender();

    virtual void setImage(int format, int width, int height, void *data);

    virtual void Init();

    virtual void Draw(int width, int height);

    virtual void Destroy();
};


#endif //OPENGLES_DOC_GLFBORENDER_H
