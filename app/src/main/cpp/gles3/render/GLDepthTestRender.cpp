//
// Created by 任振铭 on 2024/10/18.
//

#include "GLDepthTestRender.h"

glm::vec3 transPos[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.5f, 1.3f, -0.1f),
        glm::vec3(-1.3f, 1.0f, -1.5f) * 1.6f,
        glm::vec3(-1.3f, 0.0f, -1.5f),
};

GLDepthTestRender::GLDepthTestRender() {

}

GLDepthTestRender::~GLDepthTestRender() {

}

void GLDepthTestRender::Init() {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, mImage.image_data);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    char vertex_shader[] = "#version 300 es\n"
                           "layout(location = 0) in vec4 position;\n"
                           "layout(location = 1) in vec2 tex_position;\n"
                           "out vec2 o_tex_position;\n"
                           "uniform mat4 mvp_matrix;\n"
                           "void main(){\n"
                           "gl_Position = mvp_matrix * position;\n"
                           "o_tex_position = tex_position;\n"
                           "}\n";

    char fragment_shader[] = "#version 300 es\n"
                             "precision mediump float;\n"
                             "in vec2 o_tex_position;\n"
                             "uniform sampler2D u_texture;\n"
                             "layout(location = 0) out vec4 fragColor;\n"
                             "void main(){\n"
                             "fragColor = texture(u_texture,o_tex_position);\n"
                             "}\n";
    mVertexShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    mFragmentShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    mProgram = OpenglUtils::CreateProgram(mVertexShader, mFragmentShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLDepthTestRender CreateProgram vertex_shader:%d",
                        mVertexShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLDepthTestRender CreateProgram fragment_shader:%d",
                        mFragmentShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLDepthTestRender CreateProgram program:%d",
                        mProgram);

    mvpMatrixLocation = glGetUniformLocation(mProgram, "mvp_matrix");
    textureLocation = glGetUniformLocation(mProgram, "u_texture");
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLDepthTestRender CreateProgram mvpMatrixLocation:%d,textureLocation:%d ",
                        mvpMatrixLocation, textureLocation);

    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          (const void *) (3 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);
}

void GLDepthTestRender::setImage(int format, int width, int height, void *data) {
    mImage.width = width;
    mImage.height = height;
    if (mImage.image_data == nullptr) {
        mImage.image_data = (unsigned char *) malloc(width * height * 4);
    }
    memcpy(mImage.image_data, data, width * height * 4);
}

void GLDepthTestRender::UpdateMatrix(float rotateX, float rotateY) {
    this->rotateX = rotateX;
    this->rotateY = rotateY;
}

void
GLDepthTestRender::UpdateMVPMatrix(glm::mat4 &mvp_matrix, int xAngle, int yAngle, float scale,
                                   glm::vec3 transVec3, float ratio) {
    xAngle = xAngle % 360;
    yAngle = yAngle % 360;

    float radiansX = PI / 180.0f * xAngle;
    float radiansY = PI / 180.0f * yAngle;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    model = glm::rotate(model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, transVec3);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3),
                                 glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 projection = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
    mvp_matrix = projection * view * model;
}

void GLDepthTestRender::Draw(int width, int height) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(mProgram);
    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(textureLocation, 0);
    for (int i = 0; i < sizeof(transPos) / sizeof(transPos[0]); i++) {
        UpdateMVPMatrix(mvp_matrix, rotateX, rotateY, 1, transPos[i],
                        (float) width / height);
        glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvp_matrix[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void GLDepthTestRender::Destroy() {
    if (mProgram) {
        glDeleteProgram(mProgram);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        glDeleteTextures(1, &textureId);
        mProgram = GL_NONE;
        vao = GL_NONE;
        vbo = GL_NONE;
    }
}