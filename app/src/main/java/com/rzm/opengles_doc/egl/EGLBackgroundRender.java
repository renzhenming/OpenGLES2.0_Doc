package com.rzm.opengles_doc.egl;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;

public class EGLBackgroundRender {

    private final Context mContext;
    private Bitmap mBitmap;
    private int mWidth;
    private int mHeight;

    public EGLBackgroundRender(Context context) {
        this.mContext = context;
    }

    public void init(Bitmap bmp, int width, int height) {
        this.mBitmap = bmp;
        this.mWidth = width;
        this.mHeight = height;
        init(mWidth, mHeight, mContext.getAssets());
    }

    public native void init(int mWidth, int mHeight, AssetManager assets);

    public Bitmap draw() {
        return drawNative();
    }

    public native Bitmap drawNative();
}
