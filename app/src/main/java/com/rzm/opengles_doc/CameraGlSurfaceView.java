package com.rzm.opengles_doc;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.rzm.opengles_doc.render.CameraRender;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class CameraGlSurfaceView extends GLSurfaceView implements GLSurfaceView.Renderer {
    private final CameraRender mRender;

    public CameraGlSurfaceView(Context context, CameraRender render) {
        super(context);
        this.mRender = render;
        this.mRender.bindSurfaceView(this);
        init();
    }

    private void init() {
        setEGLContextClientVersion(2);
        setRenderer(this);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mRender.onSurfaceCreated(gl, config);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mRender.onSurfaceChanged(gl, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        mRender.onDrawFrame(gl);
    }

    public void switchCamera() {
        mRender.switchCamera();
    }
}
