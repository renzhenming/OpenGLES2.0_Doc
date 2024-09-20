//
// Created by 任振铭 on 2024/9/18.
//

#include "RenderManager.h"
#include "header.h"
#include "GLTriangleRender.h"
#include "GLTextureRender.h"

RenderManager *RenderManager::render_manager = nullptr;


RenderManager *RenderManager::Get() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager Get");
    if (render_manager == nullptr) {
        render_manager = new RenderManager();
    }
    return render_manager;
}

RenderManager::RenderManager() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager init");
    mCurrentRender = new GLTriangleRender();
    mLastRender = nullptr;
}

RenderManager::~RenderManager() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager destroy");
    if (mCurrentRender != nullptr) {
        mCurrentRender->Destroy();
        delete mCurrentRender;
        mCurrentRender = nullptr;
    }
    if (mLastRender != nullptr) {
        mLastRender->Destroy();
        delete mLastRender;
        mLastRender = nullptr;
    }
}

void RenderManager::SetRenderType(int renderType) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager SetRenderType %d ", renderType);
    mLastRender = mCurrentRender;
    switch (renderType) {
        case RENDER_TYPE_TRIANGLE:
            mCurrentRender = new GLTriangleRender();
            break;
        case RENDER_TYPE_TEXTURE:
            mCurrentRender = new GLTextureRender();
            break;
    }
}

void RenderManager::UpdateMatrix(float rotateX, float rotateY, float scaleX, float scaleY) {
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "RenderManager UpdateMatrix rotateX:%d rotateY:%d scaleX:%d scaleY:%d",
                        rotateX, rotateY, scaleX, scaleY);
}

void RenderManager::SetImage(int format, int width, int height, void *image_data) {
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "RenderManager SetImage format:%d width:%d height:%d",
                        format, width, height);
    if (mCurrentRender != nullptr) {
        mCurrentRender->setImage(format, width, height, image_data);
    }
}

void RenderManager::OnSurfaceCreated() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager OnSurfaceCreated");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void RenderManager::OnSurfaceChanged(int width, int height) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager OnSurfaceChanged %d, %d", width,
                        height);
    mWidth = width;
    mHeight = height;
    glViewport(0, 0, width, height);
}

void RenderManager::OnDrawFrame() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager OnDrawFrame");
    if (mLastRender != nullptr) {
        mLastRender->Destroy();
        delete mLastRender;
        mLastRender = nullptr;
    }
    if (mCurrentRender != nullptr) {
        mCurrentRender->Init();
        mCurrentRender->Draw(mWidth, mHeight);
    }
}

void RenderManager::Destroy() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager Destroy");
    if (render_manager != nullptr) {
        delete render_manager;
        render_manager = nullptr;
    }
}
