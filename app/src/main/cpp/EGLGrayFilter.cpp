//
// Created by 任振铭 on 2024/8/28.
//

#include "EGLGrayFilter.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"

static NativeAssetsLoader *loader;

EGLGrayFilter::EGLGrayFilter(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

EGLGrayFilter::~EGLGrayFilter() {

}

void EGLGrayFilter::init() {
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("egl_gray_vertex.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("egl_gray_fragment.fs", file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "vPosition");
    coordinateLocation = glGetAttribLocation(program, "vCoordinate");
    textureLocation = glGetUniformLocation(program, "vTexture");
    __android_log_print(ANDROID_LOG_INFO, "rzm", "init");
}

void EGLGrayFilter::setBitmap(void *pixel, int width, int height, int format) {
    texture = CreateTexture2D(pixel, width, height, GL_RGBA, GL_RGBA);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "setBitmap texture = %d，format = %d,", texture,
                        format);
}

void EGLGrayFilter::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(coordinateLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, elg_gray_pos);
    glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, false, 0, egl_gray_coordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(coordinateLocation);
    glUseProgram(0);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "draw end");
}
