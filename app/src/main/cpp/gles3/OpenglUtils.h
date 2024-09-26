//
// Created by 任振铭 on 2024/9/18.
//

#ifndef OPENGLES_DOC_OPENGLUTILS_H
#define OPENGLES_DOC_OPENGLUTILS_H

#include "header.h"

#define TAGS "rzm"
#define LOG(...) __android_log_print(ANDROID_LOG_INFO,TAGS,__VA_ARGS__)
#define CHECK_GL_ERROR(...) LOG("CHECK_GL_ERROR function:%s, glGetError:%s, line:%d ",__FUNCTION__,glGetError(),__LINE__)

class OpenglUtils {
public:
    static GLuint CompileShader(GLenum shader_type, const char *shader_sources);

    static GLuint CreateProgram(GLuint vertex_shader, GLuint fragment_shader);

    static void checkGlError(const char *op);
};


#endif //OPENGLES_DOC_OPENGLUTILS_H
