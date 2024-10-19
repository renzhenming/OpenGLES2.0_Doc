//
// Created by 任振铭 on 2024/10/18.
//

#ifndef OPENGLES_DOC_GLDEPTHTESTRENDER_H
#define OPENGLES_DOC_GLDEPTHTESTRENDER_H

#include "GLBaseRender.h"

#define PI 3.1415926

class GLDepthTestRender : public GLBaseRender {
public:
    GLuint textureId;
    GLuint vbo;
    GLuint vao;
    GLfloat rotateX;
    GLfloat rotateY;
    glm::mat4 mvp_matrix;
    GLint mvpMatrixLocation;
    GLint textureLocation;

    GLDepthTestRender();

    virtual ~GLDepthTestRender();

    virtual void Init();

    virtual void setImage(int format, int width, int height, void *data);

    virtual void UpdateMatrix(float rotateX, float rotateY);

    void UpdateMVPMatrix(glm::mat4 &mvp_matrix, int xAngle, int yAngle, float scale, glm::vec3 transVec3,
                    float ratio);

    virtual void Draw(int width, int height);

    virtual void Destroy();
};


#endif //OPENGLES_DOC_GLDEPTHTESTRENDER_H
