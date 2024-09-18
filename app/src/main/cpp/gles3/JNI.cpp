//
// Created by 任振铭 on 2024/9/17.
//

#include <jni.h>
#include "header.h"
#include "RenderManager.h"

#define NATIVE_RENDER_CLASS "com/rzm/opengles_doc/gles3/NativeRender"


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Init(JNIEnv *env, jobject obj) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI Init");
    RenderManager::Get();
}

JNIEXPORT void JNICALL Destroy(JNIEnv *env, jobject obj) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI Destroy");
    RenderManager::Destroy();
}

JNIEXPORT void JNICALL SetRenderType(JNIEnv *env, jobject obj, jint renderType) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI SetRenderType");
    RenderManager::Get()->SetRenderType(renderType);
}

JNIEXPORT void JNICALL
UpdateMatrix(JNIEnv *env, jobject obj, jfloat rotateX, jfloat rotateY, jfloat scaleX,
             jfloat scaleY) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI UpdateMatrix");
    RenderManager::Get()->UpdateMatrix(rotateX, rotateY, scaleX, scaleY);
}

JNIEXPORT void JNICALL
SetImage(JNIEnv *env, jobject obj, jint format, jint width, jint height, jbyteArray image_data) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI SetImage");
    jsize length = env->GetArrayLength(image_data);
    unsigned char *buf = new unsigned char[length];
    env->GetByteArrayRegion(image_data, 0, length, (jbyte *) buf);
    RenderManager::Get()->SetImage(format, width, height, buf);
    //有人问这里直接删除内存了，不会出错吗，其实在SetImage中会进行数据拷贝，所以删除没有关系
    delete[]buf;
    env->DeleteLocalRef(image_data);
}

JNIEXPORT void JNICALL OnSurfaceCreated(JNIEnv *env, jobject obj) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI OnSurfaceCreated");
    RenderManager::Get()->OnSurfaceCreated();
}

JNIEXPORT void JNICALL OnSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI OnSurfaceChanged");
    RenderManager::Get()->OnSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL OnDrawFrame(JNIEnv *env, jobject obj) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI OnDrawFrame");
    RenderManager::Get()->OnDrawFrame();
}

#ifdef __cplusplus
}
#endif

static JNINativeMethod methods[] = {
        {"init",             "()V",      (void *) (Init)},
        {"destroy",          "()V",      (void *) (Destroy)},
        {"setRenderType",    "(I)V",     (void *) (SetRenderType)},
        {"updateMatrix",     "(FFFF)V",  (void *) (UpdateMatrix)},
        {"setImage",         "(III[B)V", (void *) (SetImage)},
        {"onSurfaceCreated", "()V",      (void *) (OnSurfaceCreated)},
        {"onSurfaceChanged", "(II)V",    (void *) (OnSurfaceChanged)},
        {"onDrawFrame",      "()V",      (void *) (OnDrawFrame)},
};

extern "C" jint JNI_OnLoad(JavaVM *vm, void *p) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI_OnLoad");
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "GetEnv fail");
        return JNI_ERR;
    }
    jclass native_render_class = env->FindClass(NATIVE_RENDER_CLASS);
    if (native_render_class == nullptr) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "find NativeRender fail");
        return JNI_ERR;
    }
    jint result = env->RegisterNatives(native_render_class, methods,
                                       sizeof(methods) / sizeof(methods[0]));
    if (result < 0) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "RegisterNatives fail");
        return JNI_ERR;
    }
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI_OnLoad success");
    return JNI_VERSION_1_6;
}


extern "C" jint JNI_OnUnLoad(JavaVM *vm, void *p) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI_OnUnLoad");
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI_OnUnLoad GetEnv fail");
        return JNI_ERR;
    }
    jclass native_render_class = env->FindClass(NATIVE_RENDER_CLASS);
    jint result = env->UnregisterNatives(native_render_class);
    if (result < 0) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "JNI_OnUnLoad UnregisterNatives fail");
    }
}
