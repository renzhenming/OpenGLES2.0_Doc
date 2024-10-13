//
// Created by 任振铭 on 2024/8/31.
//

#include "EtcRender.h"
#include "GLUtils.h"
#include <vector>

EtcRender::EtcRender(JNIEnv *env, jobject obj, jobject asset) {
    render_obj = env->NewGlobalRef(obj);
    env->GetJavaVM(&vm);
    loader = new NativeAssetsLoader(env, asset);
    jclass renderClass = env->GetObjectClass(render_obj);
    jmethodID getReaderMethodId = env->GetMethodID(renderClass, "getReader",
                                                   "()Lcom/rzm/opengles_doc/utils/ZipPkmReader;");
    jobject reader = env->CallObjectMethod(render_obj, getReaderMethodId);
    reader_obj = env->NewGlobalRef(reader);
    jclass reader_class = env->GetObjectClass(reader_obj);
    getNextTextureMethodId = env->GetMethodID(reader_class, "getNextTexture",
                                              "()Landroid/opengl/ETC1Util$ETC1Texture;");
    jclass byteBuffer_class = env->FindClass("java/nio/ByteBuffer");
    remainingMethodId = env->GetMethodID(byteBuffer_class, "remaining", "()I");

    jclass etc_class = env->FindClass("android/opengl/ETC1Util$ETC1Texture");
    getWidthMethodId = env->GetMethodID(etc_class, "getWidth", "()I");
    getHeightMethodId = env->GetMethodID(etc_class, "getHeight", "()I");
    getDataMethodId = env->GetMethodID(etc_class, "getData", "()Ljava/nio/ByteBuffer;");
}

EtcRender::~EtcRender() {

}

GLuint EtcRender::initPkmTexture() {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void EtcRender::CreateSurface() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    int file_size;
    texture = initPkmTexture();
    alphaTexture = initPkmTexture();
    unsigned char *vertex_shader_code = loader->LoadFile("pkm_vertex_shader.vs", file_size);
    unsigned char *fragment_shader_code = loader->LoadFile("pkm_fragment_shader.fs", file_size);
    program = CreateProgram(vertex_shader_code, fragment_shader_code);
    positionLocation = glGetAttribLocation(program, "vPosition");
    coordinateLocation = glGetAttribLocation(program, "vCoordinate");
    modelMatrixLocation = glGetUniformLocation(program, "U_ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "U_ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "U_ProjectionMatrix");
    textureLocation = glGetUniformLocation(program, "vTexture");
    alphaTextureLocation = glGetUniformLocation(program, "vTextureAlpha");

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                             glm::vec3(0.0f, 1.0f, 0.0f));
    __android_log_print(ANDROID_LOG_INFO, "rzm", "texture=%d", texture);
}

void EtcRender::SurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float ratio = (width > height) ? width / (float) height : height / (float) width;
    if (width > height) {
        projectionMatrix = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 3.0f, 5.0f);
    } else {
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -ratio, ratio, 3.0f, 5.0f);
    }
}

void EtcRender::loadNextTextureInfo(jbyte *&texture_buffer, int &texture_width, int &texture_height,
                                    int &texture_size) {
    JNIEnv *env;
    if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "AttachCurrentThread fail");
        return;
    }

    jobject pkm_texture_obj = env->CallObjectMethod(reader_obj, getNextTextureMethodId);
    if (pkm_texture_obj == nullptr) {
        __android_log_print(ANDROID_LOG_INFO, "rzm", "pkm_texture_obj null");
        return;
    }
    texture_width = env->CallIntMethod(pkm_texture_obj, getWidthMethodId);
    texture_height = env->CallIntMethod(pkm_texture_obj, getHeightMethodId);
    jobject texture_data = env->CallObjectMethod(pkm_texture_obj, getDataMethodId);
    texture_buffer = static_cast<jbyte *>(env->GetDirectBufferAddress(texture_data));
    texture_size = env->CallIntMethod(texture_data, remainingMethodId);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "texture_width=%d", texture_width);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "texture_height=%d", texture_height);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "texture_size=%d", texture_size);
}

void EtcRender::DrawFrame() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    jbyte *texture_buffer;
    int texture_width;
    int texture_height;
    int texture_size;
    loadNextTextureInfo(texture_buffer, texture_width, texture_height, texture_size);

    if (texture_buffer == nullptr) {
        return;
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_ETC1_RGB8_OES, texture_width, texture_height, 0,
                           texture_size, texture_buffer);
    glUniform1i(textureLocation, 0);

    jbyte *texture_buffer2;
    int texture_width2;
    int texture_height2;
    int texture_size2;
    loadNextTextureInfo(texture_buffer2, texture_width2, texture_height2, texture_size2);
    if (texture_buffer2 == nullptr){
        return;
    }
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, alphaTexture);
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_ETC1_RGB8_OES, texture_width2, texture_height2, 0, texture_size2, texture_buffer2);
    glUniform1i(alphaTextureLocation, 1);

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(coordinateLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, texture_image_pos);
    glVertexAttribPointer(coordinateLocation, 2, GL_FLOAT, false, 0, texture_image_coordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(coordinateLocation);
    glUseProgram(0);
}

