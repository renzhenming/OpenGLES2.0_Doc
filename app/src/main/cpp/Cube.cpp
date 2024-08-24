//
// Created by 任振铭 on 2024/8/24.
//

#include "Cube.h"

float Cube::cubePositions[] = {
        -1.0f, 1.0f, 1.0f,    //正面左上0
        -1.0f, -1.0f, 1.0f,   //正面左下1
        1.0f, -1.0f, 1.0f,    //正面右下2
        1.0f, 1.0f, 1.0f,     //正面右上3
        -1.0f, 1.0f, -1.0f,    //反面左上4
        -1.0f, -1.0f, -1.0f,   //反面左下5
        1.0f, -1.0f, -1.0f,    //反面右下6
        1.0f, 1.0f, -1.0f,     //反面右上7
};
short Cube::index[] = {
        6, 7, 4, 6, 4, 5,    //后面
        6, 3, 7, 6, 2, 3,    //右面
        6, 5, 1, 6, 1, 2,    //下面
        0, 3, 2, 0, 2, 1,    //正面
        0, 1, 5, 0, 5, 4,    //左面
        0, 7, 3, 0, 4, 7,    //上面
};

float Cube::color[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
};

Cube::Cube(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

Cube::~Cube() {

}

void Cube::create() {
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("transform_vertex_shader.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("transform_fragment_shader.fs",
                                                           file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "a_Position");
    colorLocation = glGetAttribLocation(program, "a_Color");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");

    modelMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0, 0.0, 0.0f),
                             glm::vec3(0.0, 1.0f, 0.0f));
}

void
Cube::translateRotateScale() {
    //平移旋转缩放是对模型矩阵的操作
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 6.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(2.50, 2.5, 2.5));
}

void Cube::onChanged(int width, int height) {
    float ratio = (width > height) ? width / (float) height : height / (float) width;
    if (width > height) {
        projectionMatrix = glm::ortho(-ratio * 6, ratio * 6, -6.0f, 6.0f, 3.0f, 20.0f);
    } else {
        projectionMatrix = glm::ortho(-6.0f, 6.0f, -ratio * 6, ratio * 6, 3.0f, 20.0f);
    }
}

void Cube::draw() {
    glUseProgram(program);
    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, 0, cubePositions);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, false, 0, color);

    glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, false, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, false, glm::value_ptr(projectionMatrix));

    glDrawElements(GL_TRIANGLES, sizeof(index) / sizeof(index[0]), GL_UNSIGNED_SHORT, index);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
    glUseProgram(0);
}