package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.GrayTextureImageRender;
import com.rzm.opengles_doc.render.TextureImageRender;

public class GrayTextureImageActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        GrayTextureImageRender render = new GrayTextureImageRender(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, render);
        setContentView(surfaceView);
    }
}