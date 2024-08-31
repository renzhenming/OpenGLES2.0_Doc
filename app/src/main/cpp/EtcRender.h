//
// Created by 任振铭 on 2024/8/31.
//

#ifndef OPENGLES_DOC_ETCRENDER_H
#define OPENGLES_DOC_ETCRENDER_H

#include "header.h"
#include "NativeAssetsLoader.h"

class EtcRender {
public:
    JavaVM *vm;
    jobject render_obj;
    jmethodID getWidthMethodId;
    jmethodID getHeightMethodId;
    jmethodID getDataMethodId;
    jmethodID remainingMethodId;


    GLuint program;
    GLint positionLocation;
    GLint coordinateLocation;
    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;
    GLint textureLocation;
    GLint alphaTextureLocation;
    GLuint texture;
    GLuint alphaTexture;
    int texture_file_size = 0;
    int alpha_texture_file_size = 0;
    unsigned char *lbjn_0091_content;
    unsigned char *lbjn_0091_alpha_content;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    int image_width;
    int image_height;

    NativeAssetsLoader *loader;

    EtcRender(JNIEnv *env, jobject obj, jobject asset);

    ~EtcRender();

    GLuint initPkmTexture();

    void CreateSurface();

    void SurfaceChanged(int with, int height);

    void DrawFrame();

    void loadNextTextureInfo(jbyte *&jbyte, int &width, int &height, int &size);
};


#endif //OPENGLES_DOC_ETCRENDER_H
