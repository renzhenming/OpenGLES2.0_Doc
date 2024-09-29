//
// Created by 任振铭 on 2024/9/28.
//

#ifndef OPENGLES_DOC_GLFBOLONGLEGRENDER_H
#define OPENGLES_DOC_GLFBOLONGLEGRENDER_H

#include "GLBaseRender.h"

class GLFboLongLegRender : public GLBaseRender {
public:
    GLint texture_location;
    GLint fbo_texture_location;
    GLuint image_texture;
    GLuint fbo_texture;
    GLuint fbo;
    GLuint vbos[6];
    GLuint vaos[2];
    GLuint fboProgram;
    GlRectF rectF;
    GLfloat length_factor;

    GLFboLongLegRender();

    virtual ~GLFboLongLegRender();

    virtual void Init();

    virtual void setImage(int format, int width, int height, void *data);

    virtual void Draw(int width, int height);

    virtual void Destroy();
};


#endif //OPENGLES_DOC_GLFBOLONGLEGRENDER_H
