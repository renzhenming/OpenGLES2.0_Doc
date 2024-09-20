package com.rzm.opengles_doc.gles3;

import android.graphics.Bitmap;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class JavaGLRender implements GLSurfaceView.Renderer {
    private final NativeRender mNativeRender;

    public JavaGLRender() {
        this.mNativeRender = new NativeRender();
    }

    public void init() {
        mNativeRender.init();
    }

    public void destroy() {
        mNativeRender.destroy();
    }

    public void setRenderType(int renderType) {
        mNativeRender.setRenderType(renderType);
    }

    public void updateMatrix(float rotateX, float rotateY, float scaleX, float scaleY) {
        mNativeRender.updateMatrix(rotateX, rotateY, scaleX, scaleY);
    }

    public void setImage(int format, int width, int height, byte[] bytes) {
        mNativeRender.setImage(format, width, height, bytes);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mNativeRender.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mNativeRender.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        mNativeRender.onDrawFrame();
    }
}
