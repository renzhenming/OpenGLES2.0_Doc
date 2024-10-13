//
// Created by 任振铭 on 2024/8/18.
//
#include "TriangleRenderWithMatrix.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"
#include "../header.h"

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
    positionLocation = glGetAttribLocation(program, "vPosition");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    colorLocation = glGetAttribLocation(program, "aColor");

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0, 0.0, 0.0f),
                             glm::vec3(0.0, 1.0f, 0.0f));
}

void TriangleRenderWithMatrix::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    float ratio = width > height ? (float) width / height : (float) height / width;
    //以较窄的一边作为1
    if (width > height) {
        //透视投影。通过将场景中的物体投影到视锥体的近平面上，可以实现透视效果，使得远处的物体看起来比近处的物体小。
        projectionMatrix = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 3.0f, 7.0f);
    } else {
        projectionMatrix = glm::frustum(-1.0f, 1.0f, -ratio, ratio, 3.0f, 7.0f);
    }
}

void TriangleRenderWithMatrix::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glUseProgram(program);

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 0, vertex_pos);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, false, 0, color);
    glEnableVertexAttribArray(colorLocation);

    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    //GL_TRIANGLES: 每个三角形都由三个顶点明确指定，没有顶点之间的共享关系
    //GL_TRIANGLE_STRIP: 一系列相连的三角形组成一个条带。第一个三角形由前三个顶点定义，后续的每个三角形通过复用前一个三角形的两个顶点并添加一个新顶点来形成。
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    glDisableVertexAttribArray(positionLocation);
}