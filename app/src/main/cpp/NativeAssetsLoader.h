//
// Created by 任振铭 on 2024/8/18.
//

#ifndef OPENGLES_DOC_NATIVEASSETSLOADER_H
#define OPENGLES_DOC_NATIVEASSETSLOADER_H

#include <jni.h>
#include "header.h"

class NativeAssetsLoader {

public:
    NativeAssetsLoader(JNIEnv *env, jobject asset);
    unsigned char *LoadFile(const char *path, int &fileSize);
};


#endif //OPENGLES_DOC_NATIVEASSETSLOADER_H
