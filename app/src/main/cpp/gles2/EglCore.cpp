//
// Created by 任振铭 on 2024/8/28.
//

#include "EglCore.h"

void EglCore::init() {
    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "eglGetDisplay fail");
        return;
    }
    if (!eglInitialize(display, 0, 0)) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "eglInitialize fail");
        return;
    }
    EGLint attributes[] = {EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
                           EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 16, EGL_RENDERABLE_TYPE,
                           EGL_OPENGL_ES2_BIT, EGL_NONE};
    int numOfConfig = 0;
    if (!eglChooseConfig(display, attributes, &config, 1, &numOfConfig)) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "eglChooseConfig fail");
        return;
    }
    EGLint attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    if (!(eglContext = eglCreateContext(display, config, EGL_NO_CONTEXT, attrib_list))) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "eglCreateContext fail");
        return;
    }
}

EGLSurface EglCore::createOffscreenSurface(int width, int height) {
    EGLint attrib_list[] = {EGL_WIDTH, width, EGL_HEIGHT, height, EGL_NONE, EGL_NONE};
    EGLSurface surface = eglCreatePbufferSurface(display, config, attrib_list);
    if (!surface) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "eglCreatePbufferSurface fail");
    }
    return surface;
}

bool EglCore::makeCurrent(EGLSurface eglSurface) {
    return eglMakeCurrent(display, eglSurface, eglSurface, eglContext);
}