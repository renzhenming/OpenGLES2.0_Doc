//
// Created by 任振铭 on 2024/8/24.
//

#include "CubeTransformRender.h"
#include "Cube.h"

static Cube *cube;

CubeTransformRender::CubeTransformRender(JNIEnv *env, jobject asset) {
    cube = new Cube(env, asset);
}

CubeTransformRender::~CubeTransformRender() {

}

void CubeTransformRender::CreateSurface() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    cube->create();
}

void CubeTransformRender::SurfaceChanged(int with, int height) {
    glViewport(0, 0, with, height);
    cube->onChanged(with, height);
}

void CubeTransformRender::DrawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cube->draw();
    cube->translateRotateScale();
    cube->draw();
}