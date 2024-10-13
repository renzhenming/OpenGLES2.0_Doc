//
// Created by 任振铭 on 2024/8/18.
//
#include "TriangleRenderVAO.h"
#include "NativeAssetsLoader.h"
#include "GLUtils.h"
#include "../header.h"

TriangleRenderVAO::TriangleRenderVAO(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

void TriangleRenderVAO::CreateSurface() {
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

    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix2 = glm::translate(modelMatrix, glm::vec3(1.0f, 1.0f, 0.0f));

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_color_pos), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_color_pos), vertex_color_pos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned short index[] = {0, 1, 2};
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(index), index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //OpenGLES 3.0版本才有的api
    //通过将顶点属性状态封装在 VAO 中，可以避免在每次渲染调用时重复设置顶点属性指针和状态。
    // 一旦 VAO 被配置好，只需要在渲染循环中绑定相应的 VAO，OpenGL 就可以直接使用其存储的状态信息进行渲染，
    // 大大减少了 CPU 的开销，提高了渲染效率。
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 4), 0);
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 4),
                          (const void *) (sizeof(float) * 3));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindVertexArray(GL_NONE);
}

void TriangleRenderVAO::SurfaceChanged(int width, int height) {
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

void TriangleRenderVAO::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //被注释的部分就是被封装进vao的部分
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glUseProgram(program);

//    glEnableVertexAttribArray(positionLocation);
//    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 4), 0);
//    glEnableVertexAttribArray(colorLocation);
//    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 4),
//                          (const void *) (sizeof(float) * 3));

    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(positionLocation);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}