//
// Created by 任振铭 on 2024/9/20.
//

#ifndef OPENGLES_DOC_GLTEXTURERENDER_H
#define OPENGLES_DOC_GLTEXTURERENDER_H

#include "GLBaseRender.h"

class GLTextureRender : public GLBaseRender {
public:
    GLint textureLocation;
    GLuint texture;
    Image image;

    GLTextureRender();

    ~GLTextureRender();

    virtual void Init();

    virtual void setImage(int format, int width, int height, void *data);

    virtual void Draw(int width, int height);

    virtual void Destroy();
};


#endif //OPENGLES_DOC_GLTEXTURERENDER_H
