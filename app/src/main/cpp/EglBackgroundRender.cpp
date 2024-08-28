//
// Created by 任振铭 on 2024/8/28.
//

#include <jni.h>
#include "EglCore.h"
#include "EGLGrayFilter.h"
#include <android/bitmap.h>

EglCore *eglCore;
EGLGrayFilter *filter;
int image_width;
int image_heigth;
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_egl_EGLBackgroundRender_init(JNIEnv *env, jobject thiz, int width,
                                                        int height, jobject asset) {
    image_width = width;
    image_heigth = height;
    eglCore = new EglCore();
    eglCore->init();
    EGLSurface surface = eglCore->createOffscreenSurface(width, height);
    eglCore->makeCurrent(surface);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "initEgl success");
    filter = new EGLGrayFilter(env, asset);
    filter->init();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_egl_EGLBackgroundRender_setBitmap(JNIEnv *env, jobject thiz,
                                                             jobject bmp) {

    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bmp, &info) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "AndroidBitmap_getInfo fail");
        return;
    }
    void *pixel;
    if (AndroidBitmap_lockPixels(env, bmp, &pixel) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "AndroidBitmap_lockPixels fail");
        return;
    }
    filter->setBitmap(pixel, info.width, info.height, info.format);
    if (AndroidBitmap_unlockPixels(env, bmp) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "AndroidBitmap_unlockPixels fail");
        return;
    }
    __android_log_print(ANDROID_LOG_INFO, "rzm", "setBitmap success");
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_rzm_opengles_1doc_egl_EGLBackgroundRender_draw(JNIEnv *env, jobject thiz) {
    filter->draw();

    jclass bitmapClass = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapMethodId = env->GetStaticMethodID(bitmapClass, "createBitmap",
                                                            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jclass configClass = env->FindClass("android/graphics/Bitmap$Config");
    jfieldID argb8888FieldId = env->GetStaticFieldID(configClass, "ARGB_8888",
                                                     "Landroid/graphics/Bitmap$Config;");
    jobject configObj = env->GetStaticObjectField(configClass, argb8888FieldId);

    jobject bitmapObject = env->CallStaticObjectMethod(bitmapClass, createBitmapMethodId,
                                                       image_width, image_heigth,
                                                       configObj);
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bitmapObject, &info) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "AndroidBitmap_getInfo fail");
        return nullptr;
    }
    void *pixel;
    if (AndroidBitmap_lockPixels(env, bitmapObject, &pixel) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "AndroidBitmap_lockPixels fail");
        return nullptr;
    }
    glReadPixels(0, 0, info.width, info.height, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    AndroidBitmap_unlockPixels(env, bitmapObject);
    return bitmapObject;
}