//
// Created by 任振铭 on 2024/8/21.
//

#include "CubeRender.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"

static NativeAssetsLoader *loader;

CubeRender::CubeRender(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

CubeRender::~CubeRender() {

}

void CubeRender::CreateSurface() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("cube_vertex_shader.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("cube_fragment_shader.fs", file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "vPosition");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    colorLocation = glGetAttribLocation(program, "aColor");
    modelMatrix = glm::translate(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(glm::vec3(5.0f, 5.0f, 10.0f), glm::vec3(0.0, 0.0, 0.0f),
                             glm::vec3(0.0, 1.0f, 0.0f));
}

void CubeRender::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    float ratio = width > height ? (float) width / height : (float) height / width;
    //以较窄的一边作为1
    if (width > height) {
        //透视投影。通过将场景中的物体投影到视锥体的近平面上，可以实现透视效果，使得远处的物体看起来比近处的物体小。
        projectionMatrix = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 3.0f, 15.0f);
    } else {
        projectionMatrix = glm::frustum(-1.0f, 1.0f, -ratio, ratio, 3.0f, 15.0f);
    }
}

void CubeRender::DrawFrame() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, false, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, false, glm::value_ptr(projectionMatrix));

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 0, cube_pos);

    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, false, 0, cube_colors);

    //GL_TRIANGLES:绘制顺序是明确的，按照给定的顶点顺序逐个绘制三角形。
    glDrawElements(GL_TRIANGLES, sizeof(cube_index) / sizeof(cube_index[0]), GL_UNSIGNED_SHORT,
                   cube_index);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
}
























