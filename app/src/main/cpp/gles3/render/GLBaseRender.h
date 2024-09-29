//
// Created by 任振铭 on 2024/9/18.
//

#ifndef OPENGLES_DOC_GLBASERENDER_H
#define OPENGLES_DOC_GLBASERENDER_H

#include "header2.h"
#include "OpenglUtils.h"

#define RENDER_TYPE_BASE                100
#define RENDER_TYPE_TRIANGLE            RENDER_TYPE_BASE
#define RENDER_TYPE_TEXTURE             RENDER_TYPE_BASE+1
#define RENDER_TYPE_YUV_TEXTURE         RENDER_TYPE_BASE+2
#define RENDER_TYPE_VAO                 RENDER_TYPE_BASE+3
#define RENDER_TYPE_FBO                 RENDER_TYPE_BASE+4
#define RENDER_TYPE_FBO_LONG_LEG        RENDER_TYPE_BASE+5

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

typedef struct GlRectF {
    float left;
    float right;
    float top;
    float bottom;

    GlRectF() {
        left = 0, right = 0, top = 0, bottom = 0;
    }
} GlRectF;

class GLBaseRender {

public:
    GLBaseRender() {
        mVertexShader = 0;
        mFragmentShader = 0;
        mProgram = 0;
        mImage.width = 0;
        mImage.height = 0;
        mImage.format = -1;
        mImage.image_data = nullptr;
    }

    virtual ~GLBaseRender() {
        LOG("~GLBaseRender");
        if (mImage.image_data != nullptr) {
            LOG("~GLBaseRender, free mImage.image_data");
            free(mImage.image_data);
            mImage.image_data = nullptr;
        }
    }

    virtual void Init() = 0;

    virtual void setImage(int format, int width, int height, void *data) {}

    virtual void Draw(int width, int height) = 0;

    virtual void Destroy() = 0;

protected:
    Image mImage;
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mProgram;
};


#endif //OPENGLES_DOC_GLBASERENDER_H
