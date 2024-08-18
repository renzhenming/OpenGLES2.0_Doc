//
// Created by 任振铭 on 2024/8/18.
//
#include "TriangleRenderWithMatrix.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"
#include "header.h"

TriangleRenderWithMatrix::TriangleRenderWithMatrix(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

void TriangleRenderWithMatrix::CreateSurface() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("simple_vertex_shader_matrix.vs",
                                                         file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("simple_fragment_shader_matrix.fs",
                                                           file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    modelMatrix = glm::translate(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0, 0.0, 0.0f),
                             glm::vec3(0.0, 1.0f, 0.0f));
}

void TriangleRenderWithMatrix::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    float ratio = (float) width / height;
    projectionMatrix = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 3.0f, 7.0f);
}

void TriangleRenderWithMatrix::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glUseProgram(program);
    int positionLocation = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 0, vertex_pos);

    GLint modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    GLint viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    GLint projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    GLint colorLocation = glGetAttribLocation(program, "aColor");
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, false, 0, color);
    glEnableVertexAttribArray(colorLocation);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(positionLocation);
}