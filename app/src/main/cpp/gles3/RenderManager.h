//
// Created by 任振铭 on 2024/9/18.
//

#ifndef OPENGLES_DOC_RENDERMANAGER_H
#define OPENGLES_DOC_RENDERMANAGER_H

#include "GLBaseRender.h"

class RenderManager {

protected:
    int mWidth;
    int mHeight;
    GLBaseRender *mCurrentRender;
    GLBaseRender *mLastRender;

    static RenderManager *render_manager;

    RenderManager();

    virtual ~RenderManager();

public:
    void SetRenderType(int renderType);

    void UpdateMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

    void SetImage(int format, int width, int height, void *image_data);

    void OnSurfaceCreated();

    void OnSurfaceChanged(int width, int height);

    void OnDrawFrame();

    static RenderManager *Get();

    static void Destroy();
};


#endif //OPENGLES_DOC_RENDERMANAGER_H
