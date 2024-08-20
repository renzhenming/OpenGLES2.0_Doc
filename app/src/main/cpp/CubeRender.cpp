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
    modelMatrix = glm::translate(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(glm::vec3(5.0f, 5.0f, 10.0f), glm::vec3(0.0, 0.0, 0.0f),
                             glm::vec3(0.0, 1.0f, 0.0f));
}

void CubeRender::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    float ratio = (float) width / height;
    projectionMatrix = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 3.0f, 15.0f);
}

void CubeRender::DrawFrame() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    GLint modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));
    GLint viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, false, glm::value_ptr(viewMatrix));
    GLint projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, false, glm::value_ptr(projectionMatrix));

    GLint positionLocation = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 0, cube_pos);

    GLint colorPosition = glGetAttribLocation(program, "aColor");
    glEnableVertexAttribArray(colorPosition);
    glVertexAttribPointer(colorPosition, 3, GL_FLOAT, false, 0, cube_colors);

    glDrawElements(GL_TRIANGLES, sizeof(cube_index) / sizeof(cube_index[0]), GL_UNSIGNED_SHORT,
                   cube_index);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorPosition);
}
























