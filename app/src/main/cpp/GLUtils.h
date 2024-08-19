//
// Created by 任振铭 on 2024/8/18.
//

#ifndef OPENGLES_DOC_GLUTILS_H
#define OPENGLES_DOC_GLUTILS_H

#include "header.h"

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

GLuint CreateShader(GLenum shader_type, const char *source_code);

GLuint CreateProgram(GLuint vertex_shader, GLuint fragment_shader);

GLuint CreateProgram(unsigned char *vertex_shader_code, unsigned char *fragment_shader_code);

static inline void checkGlError(const char *op);

#endif //OPENGLES_DOC_GLUTILS_H
