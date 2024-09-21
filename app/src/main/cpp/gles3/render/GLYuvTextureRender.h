//
// Created by 任振铭 on 2024/9/20.
//

#ifndef OPENGLES_DOC_GLYUVTEXTURERENDER_H
#define OPENGLES_DOC_GLYUVTEXTURERENDER_H

#include "GLBaseRender.h"

class GLYuvTextureRender : public GLBaseRender {
public:
    Image image;
    GLint textureYLocation;
    GLint textureUVLocation;
    GLuint textureY;
    GLuint textureUV;

    GLYuvTextureRender();

    ~GLYuvTextureRender();

    virtual void Init();

    virtual void setImage(int format, int width, int height, void *data);

    virtual void Draw(int width, int height);

    virtual void Destroy();
};


#endif //OPENGLES_DOC_GLYUVTEXTURERENDER_H
