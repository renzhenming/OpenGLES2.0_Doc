//
// Created by 任振铭 on 2024/9/20.
//

#include "GLYuvTextureRender.h"
#include "OpenglUtils.h"

GLYuvTextureRender::GLYuvTextureRender() {

}

GLYuvTextureRender::~GLYuvTextureRender() {

}

void GLYuvTextureRender::Init() {
    char vertex_shader[] = "#version 300 es\n"
                           "layout(location = 0) in vec4 position;\n"
                           "layout(location = 1) in vec2 texCoord;\n"
                           "out vec2 o_texCoord;\n"
                           "void main(){\n"
                           "gl_Position = position;\n"
                           "o_texCoord = texCoord;\n"
                           "}\n";
    char fragment_shader[] = "#version 300 es\n"
                             "precision mediump float;\n"
                             "in vec2 o_texCoord;\n"
                             "out vec4 fragColor;\n"
                             "uniform sampler2D y_texture;\n"
                             "uniform sampler2D uv_texture;\n"
                             "void main(){\n"
                             "vec3 yuv;\n"
                             "yuv.x = texture(y_texture,o_texCoord).r - 0.063;\n"
                             "yuv.y = texture(uv_texture,o_texCoord).a - 0.502;\n"
                             "yuv.z = texture(uv_texture,o_texCoord).r - 0.502;\n"
                             "highp vec3 rgb = mat3(1.164, 1.164,  1.164,		\n"
                             "                      0    , -0.392, 2.017,				\n"
                             "                      1.596, -0.813, 0.0) * yuv; 		\n"
                             "fragColor = vec4(rgb,1.0);\n"
                             "}\n";

    mVertexShader = OpenglUtils::CompileShader(GL_VERTEX_SHADER, vertex_shader);
    mFragmentShader = OpenglUtils::CompileShader(GL_FRAGMENT_SHADER, fragment_shader);
    mProgram = OpenglUtils::CreateProgram(mVertexShader, mFragmentShader);
    textureYLocation = glGetUniformLocation(mProgram, "y_texture");
    textureUVLocation = glGetUniformLocation(mProgram, "uv_texture");

    GLuint textures[2];
    glGenTextures(2, textures);
    textureY = textures[0];
    textureUV = textures[1];

    glBindTexture(GL_TEXTURE_2D, textureY);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glBindTexture(GL_TEXTURE_2D, textureUV);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLYuvTextureRender vertex_shader:%d",
                        mVertexShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLYuvTextureRender fragment_shader:%d",
                        mFragmentShader);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLYuvTextureRender program:%d",
                        mProgram);
    __android_log_print(ANDROID_LOG_INFO, "rzm", "GLYuvTextureRender textureY:%d, textureUV:%d",
                        textureY, textureUV);
}

void GLYuvTextureRender::setImage(int format, int width, int height, void *data) {
    __android_log_print(ANDROID_LOG_INFO, "rzm",
                        "GLYuvTextureRender setImage format:%d,width:%d,height=%d,",
                        format, width, height);
    if (data == nullptr) {
        return;
    }
    image.format = format;
    image.width = width;
    image.height = height;
    if (image.image_data == nullptr) {
        image.image_data = (unsigned char *) malloc(width * height * 1.5);
    }
    memcpy(image.image_data, data, width * height * 1.5);
}

void GLYuvTextureRender::Draw(int width, int height) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vertex[] = {
            -1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,

            1.0, -1.0, 0.0,
            1.0, 1.0, 0.0,
    };
    GLfloat texture_coord[] = {
            0.0, 0.0,
            0.0, 1.0,
            1.0, 1.0,
            1.0, 0.0,
    };

    GLushort index[] = {0, 1, 2, 0, 2, 3};
    glUseProgram(mProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureY);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, image.width, image.height, 0,
                 GL_LUMINANCE,
                 GL_UNSIGNED_BYTE,
                 image.image_data);
    glUniform1i(textureYLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureUV);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, image.width >> 1, image.height >> 1, 0,
                 GL_LUMINANCE_ALPHA,
                 GL_UNSIGNED_BYTE,
                 image.image_data + image.width * image.height);
    glUniform1i(textureUVLocation, 1);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), vertex);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), texture_coord);

    OpenglUtils::checkGlError("glVertexAttribPointer");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, index);
    OpenglUtils::checkGlError("glDrawElements");
    glUseProgram(GL_NONE);
}

void GLYuvTextureRender::Destroy() {
    if (mProgram) {
        glDeleteProgram(mProgram);
        glDeleteTextures(1, &textureY);
        glDeleteTextures(1, &textureUV);
        mProgram = GL_NONE;
    }
}