//
// Created by 任振铭 on 2024/8/28.
//

#ifndef OPENGLES_DOC_EGLGRAYFILTER_H
#define OPENGLES_DOC_EGLGRAYFILTER_H

#include "../header.h"

class EGLGrayFilter {
public:
    GLuint program;
    GLint positionLocation;
    GLint coordinateLocation;
    GLint textureLocation;
    GLuint texture;

    int image_width;
    int image_height;

    EGLGrayFilter(JNIEnv *env, jobject asset);

    ~EGLGrayFilter();

    void init();

    void setBitmap(void *pixel, int width, int height, int format);

    void draw();
};


#endif //OPENGLES_DOC_EGLGRAYFILTER_H
