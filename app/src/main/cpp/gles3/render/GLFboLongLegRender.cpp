//
// Created by 任振铭 on 2024/9/28.
//

#include "GLFboLongLegRender.h"

unsigned short index[] = {0, 1, 2, 0, 2, 3};
unsigned short fbo_index[] = {0, 1, 2, 0, 2, 3, 1, 4, 5, 1, 5, 2};

GLFboLongLegRender::GLFboLongLegRender() {

}

GLFboLongLegRender::~GLFboLongLegRender() {

}

void GLFboLongLegRender::Init() {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "------Init------");
    length_factor = -0.2;
    rectF.left = 0.0;
    rectF.right = 1.0;
    rectF.top = 0.5;
    rectF.right = 1.0;

    float ratio_of_wh = mImage.width * 1.0f / mImage.height;
    float ratio_of_hw = 1 / ratio_of_wh;
    if (ratio_of_wh > ratio_of_hw) {
        ratio_of_wh = 1.0f;
    } else {
        ratio_of_hw = 1.0f;
    }

    GLfloat vertex[] = {
            -0.8f * ratio_of_wh, 0.8f * ratio_of_hw + length_factor * 0.8f, 0.0f,
            -0.8f * ratio_of_wh, -0.8f * ratio_of_hw - length_factor * 0.8f, 0.0f,
            0.8f * ratio_of_wh, -0.8f * ratio_of_hw - length_factor * 0.8f, 0.0f,
            0.8f * ratio_of_wh, 0.8f * ratio_of_hw + length_factor * 0.8f, 0.0f,
    };
    GLfloat tex_coord[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
    };

    GLfloat fbo_vertex[] = {
            -1.0f, 1.0f, 0.0f,
            -1.0f, 2 * length_factor, 0.0f,
            1.0f, 2 * length_factor, 0.0f,
            1.0f, 1.0f, 0.0f,

            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
    };

    GLfloat fbo_tex_coord[] = {
            0.0f, 0.0f,
            0.0f, 0.5,
            1.0f, 0.5,
            1.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
    };

    const char vertex_shader[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 position;   \n"
            "layout(location = 1) in vec2 tex_coord;   \n"
            "out vec2 o_tex_coord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = position; \n"
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

    const char fbo_vertex_shader[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 position;   \n"
            "layout(location = 1) in vec2 tex_coord;   \n"
            "out vec2 o_tex_coord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = position; \n"
            "   o_tex_coord = tex_coord;                \n"
            "}                                          \n";

    const char fbo_fragment_shader[] =
            "#version 300 es\n"
            "precision mediump float;\n"
            "in vec2 o_tex_coord;\n"
            "layout(location = 0) out vec4 fragColor;\n"
            "uniform sampler2D u_texture;\n"
            "void main()\n"
            "{\n"
            "    vec4 fragColor = texture(u_texture, o_tex_coord);\n"
            "}";

    GLuint vShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboLongLegRender CreateProgram vShader:%d",
                        vShader);
    GLuint fShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboLongLegRender CreateProgram fShader:%d",
                        fShader);
    GLuint fbo_vShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, fbo_vertex_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboLongLegRender CreateProgram fbo_vShader:%d",
                        vShader);
    GLuint fbo_fShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fbo_fragment_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboLongLegRender CreateProgram fbo_fShader:%d",
                        fbo_fShader);

    mProgram = OpenglUtils::CreateProgram(vShader, fShader);
    fboProgram = OpenglUtils::CreateProgram(fbo_vShader, fbo_fShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboLongLegRender CreateProgram program:%d",
                        mProgram);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboLongLegRender CreateProgram fbo program:%d",
                        fboProgram);

    texture_location = glGetUniformLocation(mProgram, "u_texture");
    fbo_texture_location = glGetUniformLocation(fboProgram, "u_texture");

    //创建6个缓冲区用于存储定点数据
    glGenBuffers(6, vbos);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coord), tex_coord, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertex), fbo_vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_tex_coord), fbo_tex_coord, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[5]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fbo_index), fbo_index, GL_STATIC_DRAW);
    CHECK_GL_ERROR();

    //vao管理渲染界面顶点数组
    glGenVertexArrays(2, vaos);
    glBindVertexArray(vaos[0]);

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
    //vao管理fbo顶点数组
    glBindVertexArray(vaos[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[3]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[4]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[5]);
    CHECK_GL_ERROR();
    glBindVertexArray(GL_NONE);

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
    CHECK_GL_ERROR();


    //fbo
    //创建一个纹理附着到fbo
    glGenTextures(1, &fbo_texture);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);
    CHECK_GL_ERROR();
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG("glCheckFramebufferStatus fail");
        return;
    }
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void GLFboLongLegRender::setImage(int format, int width, int height, void *data) {
    LOG("GLFboLongLegRender setImage format:%d,width:%d,height=%d,", format, width, height);
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

void GLFboLongLegRender::Draw(int width, int height) {
    __android_log_print(ANDROID_LOG_INFO, "rzm", "------Draw------");
    glViewport(0, 0, static_cast<GLsizei>(mImage.width),
               static_cast<GLsizei>(mImage.height * (1 + 2 * length_factor)));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(fboProgram);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindVertexArray(vaos[1]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glUniform1i(fbo_texture_location, 0);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);
    CHECK_GL_ERROR();
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    glUseProgram(mProgram);
    glBindVertexArray(vaos[0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glUniform1i(texture_location, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    CHECK_GL_ERROR();
    glBindVertexArray(GL_NONE);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glUseProgram(GL_NONE);
    CHECK_GL_ERROR();
}

void GLFboLongLegRender::Destroy() {
    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
    if (fboProgram) {
        glDeleteProgram(fboProgram);
        fboProgram = 0;
    }
    if (image_texture) {
        glDeleteTextures(1, &image_texture);
        image_texture = 0;
    }
    if (fbo_texture) {
        glDeleteTextures(1, &fbo_texture);
        fbo_texture = 0;
    }
    if (vaos[0]) {
        glDeleteVertexArrays(2, vaos);
    }
    if (vbos[0]) {
        glDeleteBuffers(6, vbos);
    }
}