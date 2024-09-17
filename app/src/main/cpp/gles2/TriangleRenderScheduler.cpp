#include <jni.h>

//
// Created by 任振铭 on 2024/8/18.
//

#include "TriangleRender.h"
#include "header.h"
#include "NativeAssetsLoader.h"

static TriangleRender *render;

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_TriangleRender_On_1Native_1SurfaceCreated(JNIEnv *env,
                                                                            jobject thiz,
                                                                            jobject asset) {
    render = new TriangleRender(env, asset);
    render->CreateSurface();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_TriangleRender_On_1Native_1SurfaceChanged(JNIEnv *env,
                                                                            jobject thiz,
                                                                            jint width,
                                                                            jint height) {
    render->SurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_TriangleRender_On_1Native_1DrawFrame(JNIEnv *env, jobject thiz) {
    render->DrawFrame();
}
