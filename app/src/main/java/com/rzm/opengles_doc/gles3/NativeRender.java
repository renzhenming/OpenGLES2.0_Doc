package com.rzm.opengles_doc.gles3;

import android.graphics.Bitmap;

public class NativeRender {

    static {
        System.loadLibrary("opengles");
    }

    public static final int TYPE = 100;

    public static final int TYPE_TRIANGLE = TYPE;
    public static final int TYPE_TEXTURE_MAP = TYPE + 1;
    public static final int TYPE_YUV_TEXTURE_MAP = TYPE + 2;
    public static final int TYPE_VAO = TYPE + 3;
    public static final int TYPE_FBO = TYPE + 4;

    public static final int TYPE_FBO_LONG_LEG = TYPE + 5;
    public static final int TYPE_COORDINATE_SYSTEM = TYPE + 6;
    public static final int TYPE_DEPTH_TESTING = TYPE + 7;

    public native void init();

    public native void destroy();

    public native void setRenderType(int renderType);

    public native void updateMatrix(float rotateX, float rotateY);

    public native void setImage(int format, int width, int height, byte[] bytes);

    public native void onSurfaceCreated();

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();
}
