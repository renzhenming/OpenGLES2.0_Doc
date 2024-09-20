//
// Created by 任振铭 on 2024/9/18.
//

#ifndef OPENGLES_DOC_GLBASERENDER_H
#define OPENGLES_DOC_GLBASERENDER_H

#include "header.h"

#define RENDER_TYPE_BASE           100
#define RENDER_TYPE_TRIANGLE       RENDER_TYPE_BASE
#define RENDER_TYPE_TEXTURE        RENDER_TYPE_BASE+1

struct Image {
    int width;
    int height;
    int format;
    unsigned char *image_data;

    Image() {
        width = 0;
        height = 0;
        format = 0;
        image_data = nullptr;
    }
};

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

    virtual void setImage(int format, int width, int height, void *data) {}

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
