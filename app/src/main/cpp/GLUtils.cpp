//
// Created by 任振铭 on 2024/8/18.
//

#include "GLUtils.h"

GLuint CreateShader(GLenum shader_type, const char *source_code) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source_code, nullptr);
    glCompileShader(shader);
    GLint compile_result = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
    if (compile_result == GL_FALSE) {
        char log[1024] = {0};
        GLsizei length;
        glGetShaderInfoLog(shader, sizeof(log), &length, log);
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "CompileShader %s\ncode:\n%s\n", log,
                            source_code);
        glDeleteShader(shader);
        shader = -1;
    }
    return shader;
}

GLuint CreateProgram(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    GLint link_result = GL_TRUE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_result);
    if (link_result == GL_FALSE) {
        char log[1024] = {0};
        int length;
        glGetProgramInfoLog(program, sizeof(log), &length, log);
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "CreateProgram %s\n", log);
        glDeleteProgram(program);
        program = -1;
    }
    return program;
}

GLuint CreateProgram(unsigned char *vertex_shader_code, unsigned char *fragment_shader_code) {
    GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, (char *) vertex_shader_code);
    checkGlError("create vertex shader");
    GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, (char *) fragment_shader_code);
    checkGlError("create fragment shader");
    GLuint program = CreateProgram(vertex_shader, fragment_shader);
    checkGlError("create program");
    return program;
}

static inline void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        __android_log_print(ANDROID_LOG_ERROR, "rzm", "after %s() glError (0x%x)\n", op, error);
    }
}

GLuint
CreateTextureFromFile(const char *path, unsigned char *filecontent, int file_size, int &image_width,
                      int &image_height) {
    int channel_count;
    unsigned char *pixel = nullptr;
    if (strcmp(path + (strlen(path) - 4), ".png") == 0) {
        pixel = stbi_png_load_from_memory(filecontent, file_size, &image_width, &image_height,
                                          &channel_count, 0);
    } else if (strcmp(path + (strlen(path) - 4), ".bmp") == 0) {
        pixel = stbi_bmp_load_from_memory(filecontent, file_size, &image_width, &image_height,
                                          &channel_count, 0);
    } else if (strcmp(path + (strlen(path) - 4), ".jpg") == 0) {
        pixel = stbi_jpeg_load_from_memory(filecontent, file_size, &image_width, &image_height,
                                           &channel_count, 0);
    } else {
        delete[] filecontent;
        return 0;
    }
    __android_log_print(ANDROID_LOG_INFO, "rzm", "CreateTextureFromFile %dx%d %d filesize(%d)",
                        image_width, image_height, channel_count, file_size);
//    FlipImage(pixel, image_width, image_height, channel_count);
    GLenum pixel_format = channel_count == 3 ? GL_RGB : GL_RGBA;
    GLuint texture = CreateTexture2D(pixel, image_width, image_height, pixel_format, pixel_format);
    delete[] pixel;
    delete[] filecontent;
    return texture;
}

GLuint CreateTexture2D(void *pixel, int width, int height, GLenum gpu_format, GLenum cpu_format) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, gpu_format, width, height, 0, cpu_format, GL_UNSIGNED_BYTE,
                 pixel);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void FlipImage(unsigned char *pixel, int width, int height, int channel_count) {
    int half_height = height / 2;
    for (int y = 0; y < half_height; ++y) {
        for (int x = 0; x < width; ++x) {
            int bottom_pixel_index = y * width + x;
            int top_pixel_index = (height - y - 1) * width + x;
            if (channel_count == 3) {
                SwapRGBPixel(pixel, top_pixel_index * 3, bottom_pixel_index * 3);
            } else if (channel_count == 4) {
                SwapRGBAPixel(pixel, top_pixel_index * 4, bottom_pixel_index * 4);
            }
        }
    }
}

void SwapRGBPixel(unsigned char *pixel, int src0, int src1) {
    unsigned char src0_r = pixel[src0];
    unsigned char src0_g = pixel[src0 + 1];
    unsigned char src0_b = pixel[src0 + 2];
    pixel[src0] = pixel[src1];
    pixel[src0 + 1] = pixel[src1 + 1];
    pixel[src0 + 2] = pixel[src1 + 2];
    pixel[src1] = src0_r;
    pixel[src1 + 1] = src0_g;
    pixel[src1 + 2] = src0_b;
}

void SwapRGBAPixel(unsigned char *pixel, int src0, int src1) {
    unsigned char src0_r = pixel[src0];
    unsigned char src0_g = pixel[src0 + 1];
    unsigned char src0_b = pixel[src0 + 2];
    unsigned char src0_a = pixel[src0 + 3];
    pixel[src0] = pixel[src1];
    pixel[src0 + 1] = pixel[src1 + 1];
    pixel[src0 + 2] = pixel[src1 + 2];
    pixel[src0 + 3] = pixel[src1 + 3];
    pixel[src1] = src0_r;
    pixel[src1 + 1] = src0_g;
    pixel[src1 + 2] = src0_b;
    pixel[src1 + 3] = src0_a;
}



















