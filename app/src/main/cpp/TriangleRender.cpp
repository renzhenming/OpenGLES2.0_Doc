//
// Created by 任振铭 on 2024/8/18.
//
#include "TriangleRender.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"
#include "header.h"

TriangleRender::TriangleRender(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

void TriangleRender::CreateSurface() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("simple_vertex_shader.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("simple_fragment_shader.fs", file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "vPosition");
    colorLocation = glGetUniformLocation(program, "vColor");
}

void TriangleRender::SurfaceChanged(int with, int height) {
    glViewport(0, 0, with, height);
}

void TriangleRender::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glUseProgram(program);

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 0, vertex_pos);

    glUniform4fv(colorLocation, 1, color_pos);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(positionLocation);
}