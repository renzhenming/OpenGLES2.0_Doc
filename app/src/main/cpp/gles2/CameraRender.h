//
// Created by 任振铭 on 2024/8/25.
//

#ifndef OPENGLES_DOC_CAMERARENDER_H
#define OPENGLES_DOC_CAMERARENDER_H

#include "../header.h"
#include "GLUtils.h"
#include "NativeAssetsLoader.h"

class CameraRender {
public:
    GLuint program;
    GLint positionLocation;
    GLint coordinateLocation;
    int cameraId;
    int previewWidth;
    int previewHeight;

    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;

    GLint textureLocation;
    GLuint cameraOesTexture;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    int image_width;
    int image_height;

    NativeAssetsLoader *loader;

    CameraRender(JNIEnv *env, jobject asset);

    ~CameraRender();

    void CreateSurface();

    GLuint initCameraTexture();

    GLuint getCameraTexture();

    void SurfaceChanged(int with, int height);

    void DrawFrame();

    void setCameraId(int cameraId);

    void setPreviewWidth(int width);

    void setPreviewHeight(int height);
};


#endif //OPENGLES_DOC_CAMERARENDER_H
