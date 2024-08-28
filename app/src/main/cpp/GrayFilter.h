//
// Created by 任振铭 on 2024/8/28.
//

#ifndef OPENGLES_DOC_GRAYFILTER_H
#define OPENGLES_DOC_GRAYFILTER_H

#include "header.h"

class GrayFilter {
public:
    GLuint program;
    GLint positionLocation;
    GLint coordinateLocation;
    GLint textureLocation;
    GLuint texture;

    int image_width;
    int image_height;

    GrayFilter(JNIEnv *env, jobject asset);

    ~GrayFilter();

    void init(int width, int height);

    void draw();
};


#endif //OPENGLES_DOC_GRAYFILTER_H
