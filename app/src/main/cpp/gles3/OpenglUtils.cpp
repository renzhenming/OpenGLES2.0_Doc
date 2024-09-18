//
// Created by 任振铭 on 2024/9/18.
//

#include "OpenglUtils.h"

GLuint OpenglUtils::CompileShader(GLenum shader_type, const char *shader_sources) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_sources, nullptr);
    glCompileShader(shader);
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *buff = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, buff);
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "CompileShader fail,type:%d,info:%s",
                            shader_type, buff);
        delete[]buff;
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

GLuint OpenglUtils::CreateProgram(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *buff = (char *) malloc(length);
        glGetProgramInfoLog(program, length, nullptr, buff);
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "CreateProgram info:%s", buff);
        free(buff);
        glDeleteProgram(program);
        program = 0;
    }
    return program;
}
