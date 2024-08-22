//
// Created by 任振铭 on 2024/8/21.
//

#include "TextureImageRender.h"

TextureImageRender::TextureImageRender(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

TextureImageRender::~TextureImageRender() {

}

void TextureImageRender::CreateSurface() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("texture_image_vertex.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("texture_image_fragment.fs", file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "vPosition");
    coordinateLocation = glGetAttribLocation(program, "vCoordinate");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    textureLocation = glGetUniformLocation(program, "vTexture");

    modelMatrix = glm::translate(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));

    unsigned char *image_content = loader->LoadFile("cat.png", file_size);
    texture = CreateTextureFromFile("cat.png", image_content, file_size, image_width,
                                    image_height);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "image_width=%d,image_height=%d,texture=%d",
                        image_width,
                        image_height, texture);
}

void TextureImageRender::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    float sWH = image_width / (float) image_height;
    float sWidthHeight = width / (float) height;
    if (width > height) {
        if (sWH > sWidthHeight) {
            projectionMatrix = glm::ortho(-sWidthHeight * sWH, sWidthHeight * sWH, -1.0f, 1.0f,
                                          3.0f, 5.0f);
        } else {
            projectionMatrix = glm::ortho(-sWidthHeight / sWH, sWidthHeight / sWH, -1.0f, 1.0f,
                                          3.0f, 5.0f);
        }
    } else {
        if (sWH > sWidthHeight) {
            projectionMatrix = glm::ortho(-1.0f, 1.0f, -1 / sWidthHeight * sWH,
                                          1 / sWidthHeight * sWH, 3.0f, 5.0f);
        } else {
            projectionMatrix = glm::ortho(-1.0f, 1.0f, -sWH / sWidthHeight, sWH / sWidthHeight,
                                          3.0f, 5.0f);
        }
    }
}

void TextureImageRender::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(coordinateLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, texture_image_pos);
    glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, false, 0, texture_image_coordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(coordinateLocation);
    glUseProgram(0);
}