//
// Created by 任振铭 on 2024/8/18.
//

#include "NativeAssetsLoader.h"
#include "../header.h"

static AAssetManager *sAssetManager;

NativeAssetsLoader::NativeAssetsLoader(JNIEnv *env, jobject asset) {
    sAssetManager = AAssetManager_fromJava(env, asset);
}

unsigned char *NativeAssetsLoader::LoadFile(const char *path, int &file_size) {
    unsigned char *file_content = nullptr;
    file_size = 0;
    AAsset *asset = AAssetManager_open(sAssetManager, path, AASSET_MODE_UNKNOWN);
    if (asset != nullptr) {
        file_size = AAsset_getLength(asset);
        file_content = new unsigned char[file_size + 1];
        AAsset_read(asset, file_content, file_size);
        file_content[file_size] = 0;
        AAsset_close(asset);
    }
    return file_content;
}