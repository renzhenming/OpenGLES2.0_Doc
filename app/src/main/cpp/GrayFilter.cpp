//
// Created by 任振铭 on 2024/8/28.
//

#include "GrayFilter.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"

static NativeAssetsLoader *loader;

GrayFilter::GrayFilter(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

GrayFilter::~GrayFilter() {

}

void GrayFilter::init(int width, int height) {
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("egl_gray_vertex.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("egl_gray_fragment.fs", file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "vPosition");
    coordinateLocation = glGetAttribLocation(program, "vCoordinate");
    textureLocation = glGetUniformLocation(program, "vTexture");

    unsigned char *image_content = loader->LoadFile("cat.png", file_size);
    texture = CreateTextureFromFile("cat.png", image_content, file_size, image_width,
                                    image_height);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "image_width=%d,image_height=%d,texture=%d",
                        image_width,
                        image_height, texture);
}

void GrayFilter::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(coordinateLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, texture_image_pos);
    glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, false, 0, texture_image_coordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(coordinateLocation);
    glUseProgram(0);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "draw end");
}
