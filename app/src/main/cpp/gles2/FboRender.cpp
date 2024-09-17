//
// Created by 任振铭 on 2024/8/30.
//

#include "FboRender.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"

static NativeAssetsLoader *loader;

FboRender::FboRender(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

FboRender::~FboRender() {

}

void FboRender::CreateSurface() {
    glClearColor(0.5, 0.5, 0.5, 1.0);
    int image_size = 0;
    unsigned char *image_content = loader->LoadFile("cat.png", image_size);
    loadedTextureId = CreateTextureFromFile("cat.png", image_content, image_size, image_width,
                                            image_height);

    int file_size = 0;
    //fbo
    unsigned char *vertex_shader_code = loader->LoadFile("fbo_vertex_shader.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("fbo_fragment_shader.fs", file_size);
    fbo_program = CreateProgram(vertex_shader_code, fragment_shader_code);
    fbo_positionHandle1 = glGetAttribLocation(fbo_program, "aPosition");
    fbo_textureCoordHandle1 = glGetAttribLocation(fbo_program, "aTextureCoord");
    fbo_textureHandle1 = glGetUniformLocation(fbo_program, "uTexture");

    //window
    unsigned char *window_vertex_shader_code = loader->LoadFile("fbo_vertex_shader.vs", file_size);
    unsigned char *window_fragment_shader_code = loader->LoadFile("fbo_fragment_shader.fs",
                                                                  file_size);
    window_program = CreateProgram(window_vertex_shader_code, window_fragment_shader_code);
    window_positionHandle1 = glGetAttribLocation(window_program, "aPosition");
    window_textureCoordHandle1 = glGetAttribLocation(window_program, "aTextureCoord");
    window_textureHandle1 = glGetUniformLocation(window_program, "uTexture");
}

void FboRender::SurfaceChanged(int with, int height) {
    glViewport(0, 0, with, height);
    glGenFramebuffers(1, &frame_buffer);
    glGenTextures(1, &fbo_texture);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, with, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "frame buffer not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FboRender::DrawFrame() {
    glUseProgram(fbo_program);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

    glEnableVertexAttribArray(fbo_positionHandle1);
    glEnableVertexAttribArray(fbo_textureCoordHandle1);
    glVertexAttribPointer(fbo_positionHandle1, 2, GL_FLOAT, false, 0, fbo_pos);
    glVertexAttribPointer(fbo_textureCoordHandle1, 2, GL_FLOAT, false, 0, fbo_coord);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, loadedTextureId);
    glUniform1f(fbo_textureHandle1, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(window_program);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(window_positionHandle1);
    glEnableVertexAttribArray(window_textureCoordHandle1);
    glVertexAttribPointer(window_positionHandle1, 2, GL_FLOAT, false, 0, fbo_pos);
    glVertexAttribPointer(window_textureCoordHandle1, 2, GL_FLOAT, false, 0, fbo_coord);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glUniform1f(window_textureHandle1, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDeleteTextures(1, &fbo_texture);
    glDeleteFramebuffers(1, &frame_buffer);
    glUseProgram(0);
}