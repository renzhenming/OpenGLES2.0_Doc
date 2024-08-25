package com.rzm.opengles_doc.render;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.SurfaceTexture;
import android.opengl.GLSurfaceView;
import android.util.Log;

import com.rzm.opengles_doc.simple.camera.KitkatCamera;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class CameraRender implements GLSurfaceView.Renderer {
    private final Context mContext;
    private SurfaceTexture surfaceTexture;
    private boolean logged;
    private final KitkatCamera mCamera;
    private int cameraId = 1;
    private GLSurfaceView mSurfaceView;
    private Runnable mRunnable;

    public CameraRender(Context context) {
        this.mContext = context;
        this.mCamera = new KitkatCamera();
    }

    public void bindSurfaceView(GLSurfaceView view) {
        this.mSurfaceView = view;
    }

    public native void On_Native_SurfaceCreated(AssetManager asset);

    public native void On_Native_SurfaceChanged(int width, int height);

    public native void On_Native_DrawFrame();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        if (mRunnable != null) {
            mRunnable.run();
            mRunnable = null;
        }
        Log.d("rzm", "onSurfaceCreated");
        On_Native_SurfaceCreated(mContext.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.d("rzm", "onSurfaceChanged");
        On_Native_SurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        if (surfaceTexture != null) {
            surfaceTexture.updateTexImage();
        }
        if (!logged) {
            logged = true;
            Log.d("rzm", "onDrawFrame");
        }
        On_Native_DrawFrame();
    }

    public void switchCamera() {
        mRunnable = new Runnable() {
            @Override
            public void run() {
                mCamera.close();
                cameraId = cameraId == 1 ? 0 : 1;
            }
        };
        mSurfaceView.onPause();
        mSurfaceView.onResume();
    }

    /**
     * 由native方法调用，获取preview width
     */
    public int getCameraWidth() {
        return mCamera.getPreviewSize().x;
    }

    /**
     * 由native方法调用，获取preview height
     */
    public int getCameraHeight() {
        return mCamera.getPreviewSize().y;
    }

    /**
     * 由native方法调用, 配置textureId并启动camera预览，返回当前cameraId
     */
    public int openCameraFromNative(int textureId) {
        mCamera.open(cameraId);
        surfaceTexture = new SurfaceTexture(textureId);
        mCamera.setPreviewTexture(surfaceTexture);
        surfaceTexture.setOnFrameAvailableListener(new SurfaceTexture.OnFrameAvailableListener() {
            @Override
            public void onFrameAvailable(SurfaceTexture surfaceTexture) {
                Log.d("rzm", "onFrameAvailable");
                mSurfaceView.requestRender();
            }
        });
        mCamera.preview();
        return cameraId;
    }
}
