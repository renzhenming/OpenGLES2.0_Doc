//
// Created by 任振铭 on 2024/9/18.
//

#include "GLTriangleRender.h"
#include "OpenglUtils.h"

GLTriangleRender::GLTriangleRender() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "new GLTriangleRender");

}

GLTriangleRender::~GLTriangleRender() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "~GLTriangleRender");
}

void GLTriangleRender::Init() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTriangleRender Init");
    char vertex_shader[] = "#version 300 es\n"
                           "layout(location = 0) in vec4 position;\n"
                           "void main(){\n"
                           "gl_Position = position;\n"
                           "}\n";
    char fragment_shader[] = "#version 300 es\n"
                             "precision mediump float;\n"
                             "out vec4 fragColor;\n"
                             "void main(){\n"
                             "fragColor = vec4(0.0,0.0,1.0,1.0);\n"
                             "}\n";
    mVertexShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTriangleRender CreateProgram vertex_shader:%d", mVertexShader);
    mFragmentShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTriangleRender CreateProgram fragment_shader:%d",
                        mFragmentShader);
    mProgram = OpenglUtils::CreateProgram(mVertexShader, mFragmentShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTriangleRender CreateProgram program:%d", mProgram);
}

void GLTriangleRender::Draw(int width, int height) {
    GLfloat vertex_position[] = {
            0.0, 0.5, 0.0,
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
    };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glUseProgram(mProgram);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertex_position);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex_position) / sizeof(GLfloat));
    glUseProgram(0);
}

void GLTriangleRender::Destroy() {
    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTriangleRender Destroy mProgram = %d",
                        mProgram);
}