package com.rzm.opengles_doc.render;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class TriangleRenderWithMatrix implements GLSurfaceView.Renderer {
    private final Context context;
    private boolean logged;

    public TriangleRenderWithMatrix(Context context) {
        this.context = context;
    }

    public native void On_Native_SurfaceCreated(AssetManager asset);

    public native void On_Native_SurfaceChanged(int width, int height);

    public native void On_Native_DrawFrame();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.d("rzm", "onSurfaceCreated");
        On_Native_SurfaceCreated(context.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.d("rzm", "onSurfaceChanged");
        On_Native_SurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        if (!logged) {
            logged = true;
            Log.d("rzm", "onDrawFrame");
        }
        On_Native_DrawFrame();
    }
}
