package com.rzm.opengles_doc.gles3;

public class NativeRender {

    static {
        System.loadLibrary("opengles");
    }

    public native void init();

    public native void destroy();

    public native void setRenderType(int renderType);

    public native void updateMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

    public native void setImage(int format, int width, int height, byte[] bytes);

    public native void onSurfaceCreated();

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();
}
