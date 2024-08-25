//
// Created by 任振铭 on 2024/8/25.
//

#include "CameraRender.h"

static NativeAssetsLoader *loader;

CameraRender::CameraRender(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

CameraRender::~CameraRender() {

}

void CameraRender::CreateSurface() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("camera_oes_vertex_shader.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("camera_oes_fragment_shader.fs",
                                                           file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);

    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");

    textureLocation = glGetUniformLocation(program, "vTexture");

    positionLocation = glGetAttribLocation(program, "vPosition");
    coordinateLocation = glGetAttribLocation(program, "vCoord");

    modelMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));
    cameraOesTexture = initCameraTexture();
}

GLuint CameraRender::initCameraTexture() {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);
    return texture;
}

GLuint CameraRender::getCameraTexture() {
    return cameraOesTexture;
}

void CameraRender::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    float viewRatio = width / (float) height;
    float cameraRatio = previewWidth / (float) previewHeight;
    if (viewRatio > cameraRatio) {
        projectionMatrix = glm::ortho(-cameraRatio / viewRatio, cameraRatio / viewRatio, -1.0f,
                                      1.0f, 1.0f, 3.0f);
    } else {
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -viewRatio / cameraRatio,
                                      viewRatio / cameraRatio, 1.0f, 3.0f);
    }
    //前置摄像头旋转90度，后置摄像头旋转270度
    float radian = cameraId == 1 ? 3.1415926 / 2.0 : 3 * 3.1415926 / 2.0;
    //float degree = cameraId == 1 ? 90.0 : 270;
    //经测试，glm中的glm::radian() api 不生效，所以先用glm::degrees
    modelMatrix = glm::rotate(modelMatrix, glm::degrees(radian), glm::vec3(0.0f, 0.0f, 1.0f));
    if (cameraId == 1) {
        //前置摄像头镜像问题处理。通过在y轴上设置负的缩放比例来实现镜像效果。这是因为负的缩放比例会反转对应轴上的方向，从而产生类似于镜像的效果。
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, -1.0f, 1.0f));
    }
}

void CameraRender::DrawFrame() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, false, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, false, glm::value_ptr(projectionMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, cameraOesTexture);
    glUniform1i(textureLocation, 0);

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, texture_image_pos);
    glEnableVertexAttribArray(coordinateLocation);
    glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, false, 0, texture_image_coordinate);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(coordinateLocation);
}

void CameraRender::setCameraId(int cameraId) {
    this->cameraId = cameraId;
}

void CameraRender::setPreviewWidth(int width) {
    this->previewWidth = width;
}

void CameraRender::setPreviewHeight(int height) {
    this->previewHeight = height;
}
