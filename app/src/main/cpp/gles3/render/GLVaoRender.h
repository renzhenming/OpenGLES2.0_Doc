//
// Created by 任振铭 on 2024/9/23.
//

#ifndef OPENGLES_DOC_GLVAORENDER_H
#define OPENGLES_DOC_GLVAORENDER_H

#include "GLBaseRender.h"

class GLVaoRender : public GLBaseRender {
public:
    GLuint vbo[2];
    GLuint vao;

    virtual void Init() override;

    virtual void Draw(int width, int height) override;

    virtual void Destroy() override;
};


#endif //OPENGLES_DOC_GLVAORENDER_H
