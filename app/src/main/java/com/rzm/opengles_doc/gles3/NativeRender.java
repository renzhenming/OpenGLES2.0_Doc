package com.rzm.opengles_doc.gles3;

import android.graphics.Bitmap;

public class NativeRender {

    static {
        System.loadLibrary("opengles");
    }

    public static final int TYPE = 100;

    public static final int TYPE_TRIANGLE = TYPE;
    public static final int TYPE_TEXTURE_MAP = TYPE + 1;

    public native void init();

    public native void destroy();

    public native void setRenderType(int renderType);

    public native void updateMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

    public native void setImage(Bitmap bitmap);

    public native void onSurfaceCreated();

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();
}
