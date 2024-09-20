//
// Created by 任振铭 on 2024/9/18.
//

#ifndef OPENGLES_DOC_OPENGLUTILS_H
#define OPENGLES_DOC_OPENGLUTILS_H

#include "header.h"

class OpenglUtils {
public:
    static GLuint CompileShader(GLenum shader_type, const char *shader_sources);

    static GLuint CreateProgram(GLuint vertex_shader, GLuint fragment_shader);

    static void checkGlError(const char *op);
};


#endif //OPENGLES_DOC_OPENGLUTILS_H
