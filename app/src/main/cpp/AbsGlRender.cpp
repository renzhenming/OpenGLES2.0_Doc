//
// Created by 任振铭 on 2024/8/21.
//

#include "AbsGlRender.h"

AbsGlRender::~AbsGlRender() {

}

void AbsGlRender::CreateSurface(unsigned char *vs_code, unsigned char *fs_code) {
    ClearColor();
    program = CreateProgram(vs_code, fs_code);
    InitShader();
    texture = CreateTexture();
    __android_log_print(ANDROID_LOG_INFO, "rzm", "image_width=%d,image_height=%d,texture=%d",
                        image_width,
                        image_height, texture);
}

void AbsGlRender::InitShader() {
    positionLocation = glGetAttribLocation(program, "vPosition");
    coordinateLocation = glGetAttribLocation(program, "vCoordinate");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    textureLocation = glGetUniformLocation(program, "vTexture");
    checkGlError("InitShader");
}

void AbsGlRender::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    ConfigMatrix(width, height);
    checkGlError("OnSurfaceChanged");
}

void AbsGlRender::ConfigMatrix(int width, int height) {
    modelMatrix = glm::translate(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));
    float ratio = (width > height) ? width / (float) height : height / (float) width;
    if (width > height) {
        projectionMatrix = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 3.0f, 5.0f);
    } else {
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -ratio, ratio, 3.0f, 5.0f);
    }
}

void AbsGlRender::DrawFrame() {
    Clear();
    UseProgram();
    SetExpandData();
    BindTexture();
    Draw();
    glUseProgram(0);
}


void AbsGlRender::Clear(){
    ClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGlError("Clear");
}

void AbsGlRender::ClearColor(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkGlError("ClearColor");
}

void AbsGlRender::UseProgram(){
    glUseProgram(program);
}

void AbsGlRender::SetExpandData(){
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void AbsGlRender::BindTexture(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);
}

void AbsGlRender::Draw(){
    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(coordinateLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, texture_image_pos);
    glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, false, 0, texture_image_coordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(coordinateLocation);
    glUseProgram(0);
}