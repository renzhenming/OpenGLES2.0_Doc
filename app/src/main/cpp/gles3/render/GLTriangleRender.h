//
// Created by 任振铭 on 2024/9/18.
//

#ifndef OPENGLES_DOC_GLTRIANGLERENDER_H
#define OPENGLES_DOC_GLTRIANGLERENDER_H

#include "GLBaseRender.h"

class GLTriangleRender : public GLBaseRender {
public:
    GLTriangleRender();

    virtual ~GLTriangleRender();

    virtual void Init() override;

    virtual void Draw(int width, int height) override;

    virtual void Destroy() override;
};


#endif //OPENGLES_DOC_GLTRIANGLERENDER_H
