//
// Created by 任振铭 on 2024/10/10.
//

#ifndef OPENGLES_DOC_GLCOORDINATESYSTEMRENDER_H
#define OPENGLES_DOC_GLCOORDINATESYSTEMRENDER_H

#include "GLBaseRender.h"

#define PI 3.1415926

class GLCoordinateSystemRender : public GLBaseRender {
public:
    glm::mat4 mvp_matrix;
    float xAngle;
    float yAngle;
    GLuint vbos[3];
    GLuint vao;
    GLuint image_texture;
    GLint texture_location;
    GLint mvp_matrix_location;
    GLCoordinateSystemRender();

    virtual ~GLCoordinateSystemRender();

    virtual void Init();

    virtual void setImage(int format, int width, int height, void *data);

    virtual void UpdateMatrix(float rotateX, float rotateY);

    void UpdateMVPMatrix(glm::mat4 &mvp_matrix, int xAngle, int yAngle, float ratio);

    virtual void Draw(int width, int height);

    virtual void Destroy();
};


#endif //OPENGLES_DOC_GLCOORDINATESYSTEMRENDER_H
