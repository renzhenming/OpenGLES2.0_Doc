package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.BlurTextureImageRender;
import com.rzm.opengles_doc.render.CubeTransformRender;

public class CubeTransformActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        CubeTransformRender render = new CubeTransformRender(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, render);
        setContentView(surfaceView);
    }
}