//
// Created by 任振铭 on 2024/8/18.
//

#include "GLUtils.h"

GLuint CreateShader(GLenum shader_type, const char *source_code) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source_code, nullptr);
    glCompileShader(shader);
    GLint compile_result = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
    if (compile_result == GL_FALSE) {
        char log[1024] = {0};
        GLsizei length;
        glGetShaderInfoLog(shader, sizeof(log), &length, log);
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "CompileShader %s\ncode:\n%s\n", log,
                            source_code);
        glDeleteShader(shader);
        shader = -1;
    }
    return shader;
}

GLuint CreateProgram(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    GLint link_result = GL_TRUE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_result);
    if (link_result == GL_FALSE) {
        char log[1024] = {0};
        int length;
        glGetProgramInfoLog(program, sizeof(log), &length, log);
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "CreateProgram %s\n", log);
        glDeleteProgram(program);
        program = -1;
    }
    return program;
}

GLuint CreateProgram(unsigned char *vertex_shader_code, unsigned char *fragment_shader_code) {
    GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, (char *) vertex_shader_code);
    checkGlError("create vertex shader");
    GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, (char *) fragment_shader_code);
    checkGlError("create fragment shader");
    GLuint program = CreateProgram(vertex_shader, fragment_shader);
    checkGlError("create program");
    return program;
}

static inline void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "after %s() glError (0x%x)\n", op, error);
    }
}




















