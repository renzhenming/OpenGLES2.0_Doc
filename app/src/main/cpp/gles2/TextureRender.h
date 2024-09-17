//
// Created by 任振铭 on 2024/9/1.
//

#ifndef OPENGLES_DOC_TEXTURERENDER_H
#define OPENGLES_DOC_TEXTURERENDER_H

#include "AbsGlRender.h"

class TextureRender : public AbsGlRender {
public:
    TextureRender(JNIEnv *env, jobject assets);

    GLuint CreateTexture() override;
};


#endif //OPENGLES_DOC_TEXTURERENDER_H
