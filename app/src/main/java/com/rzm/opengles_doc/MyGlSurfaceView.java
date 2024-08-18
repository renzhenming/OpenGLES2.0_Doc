package com.rzm.opengles_doc;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class MyGlSurfaceView extends GLSurfaceView {
    public MyGlSurfaceView(Context context, GLSurfaceView.Renderer renderer) {
        super(context);
        setEGLContextClientVersion(2);
        setRenderer(renderer);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }
}
