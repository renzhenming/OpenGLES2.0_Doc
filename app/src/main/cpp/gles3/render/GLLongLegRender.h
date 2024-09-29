//
// Created by 任振铭 on 2024/9/28.
//

#ifndef OPENGLES_DOC_GLLONGLEGRENDER_H
#define OPENGLES_DOC_GLLONGLEGRENDER_H
#include "GLBaseRender.h"
class GLLongLegRender : public GLBaseRender {

public:
    GLfloat length_factor;
    GLuint fbo;
    GLuint vao[2];
    GLuint vbo[6];
    GLuint texture;
    GLuint fbo_texture;
    GLuint mFboProgram;
    GLint mTextureLocation;
    GLint mFboTextureLocation;

    GLLongLegRender();

    virtual ~GLLongLegRender();

    virtual void setImage(int format, int width, int height, void *data);

    virtual void Init();

    virtual void Draw(int width, int height);

    virtual void Destroy();
};



#endif //OPENGLES_DOC_GLLONGLEGRENDER_H
