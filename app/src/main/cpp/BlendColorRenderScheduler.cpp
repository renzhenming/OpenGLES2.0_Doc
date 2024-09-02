#include <jni.h>

//
// Created by 任振铭 on 2024/8/24.
//

#include "SquareRender.h"
#include "header.h"
#include "NativeAssetsLoader.h"
#include "TextureRender.h"

static TextureRender *render;
static NativeAssetsLoader *loader;
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_BlendColorRender_On_1Native_1SurfaceCreated(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jobject asset) {
    int file_size = 0;
    loader = new NativeAssetsLoader(env, asset);
    unsigned char *vertex_shader_code = loader->LoadFile("texture_image_vertex.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("texture_image_fragment.fs", file_size);

    render = new TextureRender(env, asset);
    render->CreateSurface(vertex_shader_code, fragment_shader_code);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_BlendColorRender_On_1Native_1SurfaceChanged(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jint width,
                                                                              jint height) {
    render->SurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_opengles_1doc_render_BlendColorRender_On_1Native_1DrawFrame(JNIEnv *env,
                                                                         jobject thiz) {
    render->DrawFrame();
}
