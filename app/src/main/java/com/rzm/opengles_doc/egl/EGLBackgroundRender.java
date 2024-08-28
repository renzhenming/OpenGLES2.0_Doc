package com.rzm.opengles_doc.egl;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;

public class EGLBackgroundRender {

    private final Context mContext;

    public EGLBackgroundRender(Context context) {
        this.mContext = context;
    }

    public void init(int width, int height) {
        init(width, height, mContext.getAssets());
    }

    public native void init(int mWidth, int mHeight, AssetManager assets);

    public native void setBitmap(Bitmap bmp);

    public native Bitmap draw();
}
