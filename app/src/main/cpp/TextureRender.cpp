//
// Created by 任振铭 on 2024/9/1.
//

#include "TextureRender.h"

static NativeAssetsLoader *loader;

TextureRender::TextureRender(JNIEnv *env, jobject assets) {
    loader = new NativeAssetsLoader(env, assets);
}

GLuint TextureRender::CreateTexture() {
    int file_size;
    unsigned char *image_content = loader->LoadFile("cat.png", file_size);
    GLuint texture = CreateTextureFromFile("cat.png", image_content, file_size, image_width,
                                           image_height);
    return texture;
}