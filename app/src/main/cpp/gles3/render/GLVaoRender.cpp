//
// Created by 任振铭 on 2024/9/23.
//

#include "GLVaoRender.h"
#include "OpenglUtils.h"

void GLVaoRender::Init() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTriangleRender Init");
    char vertex_shader[] = "#version 300 es\n"
                           "layout(location = 0) in vec4 position;\n"
                           "layout(location = 1) in vec4 color;\n"
                           "out vec4 o_color;\n"
                           "void main(){\n"
                           "gl_Position = position;\n"
                           "o_color = color;\n"
                           "}\n";
    char fragment_shader[] = "#version 300 es\n"
                             "precision mediump float;\n"
                             "in vec4 o_color;\n"
                             "out vec4 fragColor;\n"
                             "void main(){\n"
                             "fragColor = o_color;\n"
                             "}\n";
    GLuint mVertexShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLVaoRender CreateProgram vertex_shader:%d",
                        mVertexShader);
    GLuint mFragmentShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLVaoRender CreateProgram fragment_shader:%d",
                        mFragmentShader);
    mProgram = OpenglUtils::CreateProgram(mVertexShader, mFragmentShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLVaoRender CreateProgram program:%d", mProgram);

    GLfloat vertex_position[] = {
            -0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0,
            -0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,
            0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0,
            0.5f, 0.5f, 0.0f, 0.0, 0.0, 1.0,
    };

    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_position), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_position), vertex_position);
    OpenglUtils::checkGlError("glBufferData 1");

    GLushort index[] = {0, 1, 2, 0, 2, 3};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(index), index);
    OpenglUtils::checkGlError("glBufferData 2");
    //3.0版本独有的api
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6,
                          (const void *) (3 * sizeof(GLfloat)));

    glBindVertexArray(GL_NONE);
}

void GLVaoRender::Draw(int width, int height) {
    glUseProgram(mProgram);
    glBindVertexArray(vao);
    OpenglUtils::checkGlError("glBindVertexArray");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *) 0);
    glBindVertexArray(GL_NONE);
}

void GLVaoRender::Destroy() {
    if (mProgram) {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(2, vbo);
        glDeleteProgram(mProgram);
        mProgram = GL_NONE;
    }
}