#include <jni.h>

//
// Created by 任振铭 on 2024/8/24.
//

#include "SquareRender.h"
#include "../header.h"
#include "NativeAssetsLoader.h"
#include "CameraRender.h"

static CameraRender *render;

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_CameraRender_On_1Native_1SurfaceCreated(JNIEnv
                                                                          *env,
                                                                          jobject thiz,
                                                                          jobject
                                                                          asset) {
    render = new CameraRender(env, asset);
    render->CreateSurface();
    GLuint texture = render->getCameraTexture();
    jclass cameraRenderClass = env->GetObjectClass(thiz);
    jmethodID openCameraMethodId = env->GetMethodID(cameraRenderClass, "openCameraFromNative",
                                                    "(I)I");
    int cameraId = env->CallIntMethod(thiz, openCameraMethodId, (int) texture);
    render->setCameraId(cameraId);
    jmethodID getWidthId = env->GetMethodID(cameraRenderClass, "getCameraWidth", "()I");
    jmethodID getHeightId = env->GetMethodID(cameraRenderClass, "getCameraHeight", "()I");
    int width = env->CallIntMethod(thiz, getWidthId);
    int height = env->CallIntMethod(thiz, getHeightId);
    render->setPreviewWidth(width);
    render->setPreviewHeight(height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_CameraRender_On_1Native_1SurfaceChanged(JNIEnv
                                                                          *env,
                                                                          jobject thiz,
                                                                          jint
                                                                          width,
                                                                          jint height) {
    render->SurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_CameraRender_On_1Native_1DrawFrame(JNIEnv
                                                                     *env,
                                                                     jobject thiz) {
    render->DrawFrame();
}
