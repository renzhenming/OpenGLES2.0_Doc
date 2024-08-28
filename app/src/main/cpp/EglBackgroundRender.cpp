//
// Created by 任振铭 on 2024/8/28.
//

#include <jni.h>
#include "EglCore.h"

EglCore *eglCore;

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_egl_EGLBackgroundRender_initEgl(JNIEnv *env, jobject thiz, int width,
                                                           int height) {

    eglCore = new EglCore();
    eglCore->init();
    EGLSurface surface = eglCore->createOffscreenSurface(width, height);
    eglCore->makeCurrent(surface);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "initEgl success");
}