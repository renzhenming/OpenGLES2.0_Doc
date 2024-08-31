package com.rzm.opengles_doc.render;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.ETC1;
import android.opengl.ETC1Util;
import android.opengl.GLSurfaceView;
import android.util.Log;

import com.rzm.opengles_doc.utils.ZipPkmReader;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.zip.ZipInputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class EtcRender implements GLSurfaceView.Renderer {
    private final Context context;
    private final ZipPkmReader mReader;
    private boolean logged;
    private GLSurfaceView mView;

    public EtcRender(Context context) throws IOException {
        this.context = context;
        this.mReader = new ZipPkmReader(context, "pkm.zip");
    }

    public void setGlSurfaceView(GLSurfaceView view) {
        this.mView = view;
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

    public ZipPkmReader getReader() {
        return mReader;
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        if (!logged) {
            logged = true;
            Log.d("rzm", "onDrawFrame");
        }
        try {
//            ETC1Util.ETC1Texture texture = mReader.getNextTexture();
//            if (texture == null) {
//                return;
//            }
//            ByteBuffer data = texture.getData();
//            int remaining = data.remaining();
//            int width = texture.getWidth();
//            int height = texture.getHeight();
            long startTime = System.currentTimeMillis();
            On_Native_DrawFrame();
            long s = System.currentTimeMillis() - startTime;
            if (s < 30) {
                try {
                    Thread.sleep(30 - s);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            mView.requestRender();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
