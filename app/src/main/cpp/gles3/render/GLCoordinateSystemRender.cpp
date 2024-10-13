//
// Created by 任振铭 on 2024/10/10.
//

#include "GLCoordinateSystemRender.h"

GLCoordinateSystemRender::GLCoordinateSystemRender() {

}

GLCoordinateSystemRender::~GLCoordinateSystemRender() {

}

void GLCoordinateSystemRender::Init() {
    //生成一个纹理
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, mImage.image_data);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLCoordinateSystemRender image_texture:%d", image_texture);
    CHECK_GL_ERROR();

    const char vertex_shader[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 position;   \n"
            "layout(location = 1) in vec2 tex_coord;   \n"
            "uniform mat4 mvp_matrix;   \n"
            "out vec2 o_tex_coord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = mvp_matrix * position; \n"
            "   o_tex_coord = tex_coord;                \n"
            "}                                          \n";

    const char fragment_shader[] =
            "#version 300 es\n"
            "precision mediump float;\n"
            "in vec2 o_tex_coord;\n"
            "layout(location = 0) out vec4 fragColor;\n"
            "uniform sampler2D u_texture;\n"
            "void main()\n"
            "{\n"
            "    fragColor = texture(u_texture, o_tex_coord);\n"
            "}";
    GLuint vShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLCoordinateSystemRender CreateProgram vShader:%d",
                        vShader);
    GLuint fShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLCoordinateSystemRender CreateProgram fShader:%d",
                        fShader);
    mProgram = OpenglUtils::CreateProgram(vShader, fShader);
    texture_location = glGetUniformLocation(mProgram, "u_texture");
    mvp_matrix_location = glGetUniformLocation(mProgram, "mvp_matrix");
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLCoordinateSystemRender CreateProgram mProgram:%d，texture_location：%d,mvp_matrix_location:%d",
                        mProgram, texture_location, mvp_matrix_location);
    GLfloat vertex[] = {
            -1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,

            1.0, -1.0, 0.0,
            1.0, 1.0, 0.0,
    };
    GLfloat tex_coord[] = {
            0.0, 0.0,
            0.0, 1.0,
            1.0, 1.0,
            1.0, 0.0,
    };
    GLushort index[] = {0, 1, 2, 0, 2, 3};

    //创建3个缓冲区用于存储定点数据
    glGenBuffers(3, vbos);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coord), tex_coord, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    //vao管理渲染界面顶点数组
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
    CHECK_GL_ERROR();
    glBindVertexArray(GL_NONE);
}

void GLCoordinateSystemRender::setImage(int format, int width, int height, void *data) {
    LOG("GLCoordinateSystemRender setImage format:%d,width:%d,height=%d,", format, width, height);
    if (data == nullptr) {
        return;
    }
    mImage.format = format;
    mImage.width = width;
    mImage.height = height;
    if (mImage.image_data == nullptr) {
        mImage.image_data = (unsigned char *) malloc(width * height * 4);
    }
    memcpy(mImage.image_data, data, width * height * 4);
}

void GLCoordinateSystemRender::UpdateMatrix(float rotateX, float rotateY) {
    this->xAngle = rotateX;
    this->yAngle = rotateY;
}

void GLCoordinateSystemRender::UpdateMVPMatrix(glm::mat4 &mvp_matrix, int xAngle, int yAngle,
                                               float ratio) {
    xAngle = xAngle % 360;
    yAngle = yAngle % 360;

    float radiansX = PI / 180.0f * xAngle;
    float radiansY = PI / 180.0f * yAngle;
    LOG("GLCoordinateSystemRender UpdateMVPMatrix radiansY:%f,radiansX:%f", radiansY, radiansX);
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    //model = glm::rotate(model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    //这个版本的glm glm::rotate(model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f))方法无效
    model = glm::rotate(model, glm::degrees(radiansX), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::degrees(radiansY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3),
                                 glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 projection = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
    mvp_matrix = projection * view * model;
}

void GLCoordinateSystemRender::Draw(int width, int height) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateMVPMatrix(mvp_matrix, xAngle, yAngle, (float) width / height);
    glUseProgram(mProgram);
    glBindVertexArray(vao);
    glUniformMatrix4fv(mvp_matrix_location, 1, GL_FALSE, &mvp_matrix[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glUniform1i(texture_location, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void GLCoordinateSystemRender::Destroy() {
    if (mProgram) {
        glDeleteProgram(mProgram);
        glDeleteBuffers(3, vbos);
        glDeleteVertexArrays(1, &vao);
        glDeleteTextures(1, &image_texture);
    }
}
