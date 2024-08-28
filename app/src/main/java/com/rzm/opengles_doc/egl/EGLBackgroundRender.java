package com.rzm.opengles_doc.egl;

import android.graphics.Bitmap;

public class EGLBackgroundRender {

    private Bitmap mBitmap;
    private int mWidth;
    private int mHeight;

    public void init(Bitmap bmp, int width, int height) {
        this.mBitmap = bmp;
        this.mWidth = width;
        this.mHeight = height;
        initEgl(mWidth, mHeight);
    }

    public native void initEgl(int mWidth, int mHeight);

    public Bitmap draw() {
        return null;
    }
}
