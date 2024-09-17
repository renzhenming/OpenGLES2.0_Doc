#include <jni.h>

//
// Created by 任振铭 on 2024/8/30.
//

#include "SquareRender.h"
#include "../header.h"
#include "NativeAssetsLoader.h"
#include "FboRender.h"

static FboRender *render;

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_FboRender_On_1Native_1SurfaceCreated(JNIEnv *env,
                                                                       jobject thiz,
                                                                       jobject asset) {
    render = new FboRender(env, asset);
    render->CreateSurface();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_FboRender_On_1Native_1SurfaceChanged(JNIEnv *env,
                                                                       jobject thiz,
                                                                       jint width,
                                                                       jint height) {
    render->SurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_FboRender_On_1Native_1DrawFrame(JNIEnv *env,
                                                                  jobject thiz) {
    render->DrawFrame();
}
