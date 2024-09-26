//
// Created by 任振铭 on 2024/9/25.
//

#include "GLFboRender.h"
#include "OpenglUtils.h"

GLFboRender::GLFboRender() {

}

GLFboRender::~GLFboRender() {

}

void GLFboRender::setImage(int format, int width, int height, void *data) {
    LOG("GLFboRender setImage format:%d,width:%d,height=%d,", format, width, height);
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

void GLFboRender::Init() {
    GLfloat vertex[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
    };

    //正常纹理坐标,原点位于左上角
    GLfloat tex_coord[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
    };

    //fbo 纹理坐标与正常纹理方向不同，原点位于左下角
    GLfloat fbo_tex_coord[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
    };

    GLushort indexes[] = {0, 1, 2, 1, 3, 2};

    char vertex_shader[] = "#version 300 es\n"
                           "layout(location = 0) in vec4 position;\n"
                           "layout(location = 1) in vec2 texcoord;\n"
                           "out vec2 o_texcoord;\n"
                           "void main(){\n"
                           "gl_Position = position;\n"
                           "o_texcoord = texcoord;\n"
                           "}\n";

    char fragment_shader[] = "#version 300 es\n"
                             "precision mediump float;\n"
                             "in vec2 o_texcoord;\n"
                             "uniform sampler2D u_texture;\n"
                             "out vec4 fragColor;\n"
                             "void main(){\n"
                             "fragColor = texture(u_texture,o_texcoord);\n"
                             "}\n";
    char fbo_fragment_shader[] = "#version 300 es\n"
                                 "precision mediump float;\n"
                                 "in vec2 o_texcoord;\n"
                                 "uniform sampler2D u_texture;\n"
                                 "out vec4 fragColor;\n"
                                 "void main(){\n"
                                 "vec4 temp_color = texture(u_texture,o_texcoord);\n"
                                 "float luminance = temp_color.r*0.3+temp_color.g*0.6+temp_color.b*0.1;\n"
                                 "fragColor = vec4(vec3(luminance),temp_color.a);\n"
                                 "}\n";

    GLuint vShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboRender CreateProgram vShader:%d",
                        vShader);
    GLuint fShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboRender CreateProgram fShader:%d",
                        fShader);
    GLuint fbo_fShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fbo_fragment_shader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboRender CreateProgram fbo_fShader:%d",
                        fbo_fShader);

    mProgram = OpenglUtils::CreateProgram(vShader, fShader);
    mFboProgram = OpenglUtils::CreateProgram(vShader, fbo_fShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboRender CreateProgram program:%d", mProgram);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLFboRender CreateProgram fbo program:%d",
                        mFboProgram);

    mTextureLocation = glGetUniformLocation(mProgram, "u_texture");
    mFboTextureLocation = glGetUniformLocation(mFboProgram, "u_texture");
    __android_log_print(ANDROID_LOG_INFO, "rzm", "mTextureLocation:%d,mFboTextureLocation:%d",
                        mTextureLocation, mFboTextureLocation);

    // 生成 VBO ，加载顶点数据和索引数据
    GLuint vbo[4];
    glGenBuffers(4, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coord), tex_coord, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_tex_coord), fbo_tex_coord, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    CHECK_GL_ERROR();

    // 生成 2 个 VAO，一个用于普通渲染，另一个用于离屏渲染
    glGenVertexArrays(2, vao);

    //普通程序vao处理
    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    CHECK_GL_ERROR();
    glBindVertexArray(GL_NONE);

    //fbo程序vao
    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    CHECK_GL_ERROR();
    glBindVertexArray(GL_NONE);

    //创建一个纹理
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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

void GLFboRender::Draw(int width, int height) {
    glViewport(0, 0, mImage.width, mImage.height);
    //绘制到fbo
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glUseProgram(mFboProgram);
    glBindVertexArray(vao[1]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(mTextureLocation, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    CHECK_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindVertexArray(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);

    glViewport(0, 0, width, height);
    glUseProgram(mProgram);
    glBindVertexArray(vao[0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glUniform1i(mFboTextureLocation, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    CHECK_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
}

void GLFboRender::Destroy() {

}