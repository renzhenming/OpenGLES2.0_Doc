package com.rzm.opengles_doc.simple;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.TriangleRender;

public class SimpleShapeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TriangleRender triangleRender = new TriangleRender(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, triangleRender);
        setContentView(surfaceView);
    }
}