//
// Created by 任振铭 on 2024/8/28.
//

#ifndef OPENGLES_DOC_EGLCORE_H
#define OPENGLES_DOC_EGLCORE_H
#include "../header.h"

class EglCore {
public:
    EGLDisplay display;
    EGLConfig config;
    EGLContext eglContext;
    void init();
    EGLSurface createOffscreenSurface(int width,int height);
    bool makeCurrent(EGLSurface eglSurface);
};


#endif //OPENGLES_DOC_EGLCORE_H
