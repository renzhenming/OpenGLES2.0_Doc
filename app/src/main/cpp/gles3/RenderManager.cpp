//
// Created by 任振铭 on 2024/9/18.
//

#include "RenderManager.h"
#include "header.h"

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
}

RenderManager::~RenderManager() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager destroy");
}

void RenderManager::SetRenderType(int renderType) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager SetRenderType %d ", renderType);
}

void RenderManager::UpdateMatrix(float rotateX, float rotateY, float scaleX, float scaleY) {
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "RenderManager UpdateMatrix rotateX:%d rotateY:%d scaleX:%d scaleY:%d",
                        rotateX, rotateY, scaleX, scaleY);
}

void RenderManager::SetImage(int format, int width, int height, unsigned char *image_data) {
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "RenderManager SetImage format:%d width:%d height:%d",
                        format, width, height);
}

void RenderManager::OnSurfaceCreated() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager OnSurfaceCreated");
}

void RenderManager::OnSurfaceChanged(int width, int height) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager OnSurfaceChanged %d, %d", width,
                        height);
}

void RenderManager::OnDrawFrame() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager OnDrawFrame");
}

void RenderManager::Destroy() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "RenderManager Destroy");
    if (render_manager != nullptr) {
        delete render_manager;
        render_manager = nullptr;
    }
}
