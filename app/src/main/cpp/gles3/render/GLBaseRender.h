//
// Created by 任振铭 on 2024/9/18.
//

#ifndef OPENGLES_DOC_GLBASERENDER_H
#define OPENGLES_DOC_GLBASERENDER_H

#include "header.h"

class GLBaseRender {

public:
    GLBaseRender() {
        mVertexShader = 0;
        mFragmentShader = 0;
        mProgram = 0;
        mWidth = 0;
        mHeight = 0;
    }

    virtual ~GLBaseRender() {

    }

    virtual void Init() = 0;

    virtual void Draw(int width, int height) = 0;

    virtual void Destroy() = 0;

protected:
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mProgram;
    int mWidth;
    int mHeight;
};


#endif //OPENGLES_DOC_GLBASERENDER_H
