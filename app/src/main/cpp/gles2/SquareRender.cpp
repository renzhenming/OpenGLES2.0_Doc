//
// Created by 任振铭 on 2024/8/18.
//
#include "SquareRender.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"
#include "../header.h"

SquareRender::SquareRender(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

void SquareRender::CreateSurface() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("triangle_vertex_shader.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("triangle_fragment_shader.fs",
                                                           file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "vPosition");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    colorLocation = glGetUniformLocation(program, "vColor");
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0, 0.0, 0.0f),
                             glm::vec3(0.0, 1.0f, 0.0f));
}

void SquareRender::SurfaceChanged(int width, int height) {
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

void SquareRender::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glUseProgram(program);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 0, trianglePoints);

    float color_pos[] = {0.5f, 1.0f, 0.3f, 1.0f};
    glUniform4fv(colorLocation, 1, color_pos);

    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glDrawElements(GL_TRIANGLES, sizeof(triangleIndex)/sizeof(triangleIndex[0]), GL_UNSIGNED_SHORT,
                   triangleIndex);
    glDisableVertexAttribArray(positionLocation);
}