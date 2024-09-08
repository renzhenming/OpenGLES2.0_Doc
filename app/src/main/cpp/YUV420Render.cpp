//
// Created by 任振铭 on 2024/8/24.
//

#include "YUV420Render.h"

YUV420Render::YUV420Render(JNIEnv *env, jobject asset) {
    loader = new NativeAssetsLoader(env, asset);
}

YUV420Render::~YUV420Render() {

}

void YUV420Render::CreateSurface() {
    glClearColor(0.1f, 0.6f, 0.4f, 1.0f);
    int file_size = 0;
    unsigned char *vertex_shader_code = loader->LoadFile("yuv_420_vertex.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("yuv_420_fragment.fs", file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "a_Position");
    coordinateLocation = glGetAttribLocation(program, "a_Texcoord");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    textureYLocation = glGetUniformLocation(program, "u_TextureY");
    textureULocation = glGetUniformLocation(program, "u_TextureU");
    textureVLocation = glGetUniformLocation(program, "u_TextureV");

    modelMatrix = glm::translate(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));

    unsigned char *image_content = loader->LoadFile("yuv_420.yuv", file_size);
    //yuv_420.yuv这一帧已知宽高为1280*720，YUV内存存储的形式是先Y后U再V
    unsigned char *y_content = image_content;
    int y_size = 1280 * 720;
    unsigned char *u_content = image_content + y_size;
    int u_size = 640 * 360;
    unsigned char *v_content = image_content + y_size + u_size;
    textureY = CreateTexture2D(y_content, 1280, 720, GL_ALPHA, GL_ALPHA);
    textureU = CreateTexture2D(u_content, 640, 360, GL_ALPHA, GL_ALPHA);
    textureV = CreateTexture2D(v_content, 640, 360, GL_ALPHA, GL_ALPHA);
    delete[]image_content;
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "image_width=%d,image_height=%d,textureY=%d,textureU=%d,textureV=%d",
                        image_width,
                        image_height, textureY, textureU, textureV);
}

void YUV420Render::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    float ratio = (width > height) ? width / (float) height : height / (float) width;
    if (width > height) {
        projectionMatrix = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 3.0f, 5.0f);
    } else {
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -ratio, ratio, 3.0f, 5.0f);
    }
}

void YUV420Render::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureY);
    glUniform1i(textureVLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureU);
    glUniform1i(textureULocation, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureV);
    glUniform1i(textureVLocation, 2);

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(coordinateLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, texture_image_pos);
    glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, false, 0, texture_image_coordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(coordinateLocation);
    glUseProgram(0);
}