package com.rzm.opengles_doc;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

import com.rzm.opengles_doc.gles3.JavaGLRender;

public class MyGlSurfaceView2 extends GLSurfaceView {

    private final JavaGLRender mGLRender;
    float lastX;
    float lastY;
    float xAngle;
    float yAngle;
    private final float ratio = 180.0f / 320;

    public MyGlSurfaceView2(Context context, JavaGLRender renderer) {
        super(context);
        this.mGLRender = renderer;
        setEGLContextClientVersion(2);
        setRenderer(renderer);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction();
        float x = event.getX();
        float y = event.getY();
        switch (action) {
            case MotionEvent.ACTION_MOVE:
                float dx = x - lastX;
                float dy = y - lastY;
                xAngle += dx * ratio;
                yAngle += dy * ratio;
                break;
        }
        lastX = x;
        lastY = y;
        mGLRender.updateMatrix(xAngle, yAngle);
        Log.d("rzm-matrix", "xAngle:" + xAngle + ",yAngle:" + yAngle);
        requestRender();
        return true;
    }
}
