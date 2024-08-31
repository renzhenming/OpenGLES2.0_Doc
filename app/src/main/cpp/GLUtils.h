//
// Created by 任振铭 on 2024/8/18.
//

#ifndef OPENGLES_DOC_GLUTILS_H
#define OPENGLES_DOC_GLUTILS_H

#include "header.h"

static float cube_pos[] = {
        -1.0f, 1.0f, 1.0f,    //正面左上0
        -1.0f, -1.0f, 1.0f,   //正面左下1
        1.0f, -1.0f, 1.0f,    //正面右下2
        1.0f, 1.0f, 1.0f,     //正面右上3
        -1.0f, 1.0f, -1.0f,    //反面左上4
        -1.0f, -1.0f, -1.0f,   //反面左下5
        1.0f, -1.0f, -1.0f,    //反面右下6
        1.0f, 1.0f, -1.0f,     //反面右上7
};

static float cube_colors[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
};

static short cube_index[] = {
        6, 7, 4, 6, 4, 5,    //后面
        6, 3, 7, 6, 2, 3,    //右面
        6, 5, 1, 6, 1, 2,    //下面
        0, 3, 2, 0, 2, 1,    //正面
        0, 1, 5, 0, 5, 4,    //左面
        0, 7, 3, 0, 4, 7,    //上面
};

static float vertex_pos[] = {
        0.5f, 0.5f, 0.0f, // top
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f  // bottom right
};

static float color_pos[] = {1.0f, 1.0f, 1.0f, 1.0f};

static float color[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
};

static float trianglePoints[] = {
        -0.5f, 0.5f, 0.0f, // top left
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f  // top right
};

static short triangleIndex[] = {
        0, 1, 2, 0, 2, 3
};

static float
        texture_image_pos[] = {
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f
};

static float
        texture_image_coordinate[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};

static float
        elg_gray_pos[] = {
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,
};

static float
        egl_gray_coordinate[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};

static float fbo_pos[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
};

static float fbo_coord[] = {
        0.0, 1.0,
        0.0, 0.0,
        1.0, 1.0,
        1.0, 0.0
};

GLuint CreateShader(GLenum shader_type, const char *source_code);

GLuint CreateProgram(GLuint vertex_shader, GLuint fragment_shader);

GLuint CreateProgram(unsigned char *vertex_shader_code, unsigned char *fragment_shader_code);

static inline void checkGlError(const char *op);

void FlipImage(unsigned char *pixel, int width, int height, int channel_count);

void SwapRGBPixel(unsigned char *pixel, int src0, int src1);

void SwapRGBAPixel(unsigned char *pixel, int src0, int src1);

GLuint CreateTexture2D(void *pixel, int width, int height, GLenum gpu_format, GLenum cpu_format);

GLuint CreateCompressedTexture2D(void *pixel, int file_size, int width, int height);

GLuint
CreateTextureFromFile(const char *path, unsigned char *filecontent, int file_size, int &image_width,
                      int &image_height);

#endif //OPENGLES_DOC_GLUTILS_H
