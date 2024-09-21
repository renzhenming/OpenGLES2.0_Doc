//
// Created by 任振铭 on 2024/9/20.
//

#include "GLTextureRender.h"
#include "header.h"
#include "OpenglUtils.h"

GLTextureRender::GLTextureRender() {

}

GLTextureRender::~GLTextureRender() {

}

void GLTextureRender::Init() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    char vertex_shader[] = "#version 300 es\n"
                           "layout(location = 0) in vec4 position;\n"
                           "layout(location = 1) in vec2 texture_position;\n"
                           "out vec2 o_texture_position;\n"
                           "void main(){"
                           "gl_Position = position;\n"
                           "o_texture_position = texture_position;\n"
                           "}\n";
    char fragment_shader[] = "#version 300 es\n"
                             "precision mediump float;\n"
                             "in vec2 o_texture_position;\n"
                             "uniform sampler2D u_texture;\n"
                             "layout(location = 0) out vec4 fragColor;\n"
                             "void main(){"
                             "fragColor = texture(u_texture,o_texture_position);\n"
                             "}\n";
    mVertexShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    mFragmentShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    mProgram = OpenglUtils::CreateProgram(mVertexShader, mFragmentShader);
    textureLocation = glGetUniformLocation(mProgram, "u_texture");
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTextureRender CreateProgram vertex_shader:%d",
                        mVertexShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLTextureRender CreateProgram fragment_shader:%d",
                        mFragmentShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLTextureRender CreateProgram program:%d",
                        mProgram);

}

void GLTextureRender::setImage(int format, int width, int height, void *data) {
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLTextureRender setImage format:%d,width:%d,height=%d,",
                        format, width, height);
    if (data == nullptr) {
        return;
    }
    image.format = format;
    image.width = width;
    image.height = height;
    if (image.image_data == nullptr) {
        image.image_data = (unsigned char *) malloc(width * height * 4);
    }
    memcpy(image.image_data, data, width * height * 4);
}

void GLTextureRender::Draw(int width, int height) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vertex[] = {
            -1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,

            1.0, -1.0, 0.0,
            1.0, 1.0, 0.0,
    };
    GLfloat texture_coord[] = {
            0.0, 0.0,
            0.0, 1.0,
            1.0, 1.0,
            1.0, 0.0,
    };
    GLushort index[] = {0, 1, 2, 0, 2, 3};
    glUseProgram(mProgram);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image.image_data);
    glUniform1i(textureLocation, 0);
    OpenglUtils::checkGlError("glUniform1i");

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertex);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, texture_coord);
    OpenglUtils::checkGlError("glVertexAttribPointer");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, index);
    OpenglUtils::checkGlError("glDrawElements");
    glUseProgram(GL_NONE);
}

void GLTextureRender::Destroy() {
    if (mProgram) {
        glDeleteProgram(mProgram);
        glDeleteTextures(1, &texture);
        mProgram = 0;
    }
}
