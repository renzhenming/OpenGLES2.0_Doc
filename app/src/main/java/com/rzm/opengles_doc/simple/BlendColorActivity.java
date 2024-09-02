package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.BlendColorRender;
import com.rzm.opengles_doc.render.BlurTextureImageRender;

public class BlendColorActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        BlendColorRender render = new BlendColorRender(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, render);
        setContentView(surfaceView);
    }
}