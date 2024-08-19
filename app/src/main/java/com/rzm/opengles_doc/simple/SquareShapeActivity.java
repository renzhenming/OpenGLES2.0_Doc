package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.SquareRender;
import com.rzm.opengles_doc.render.TriangleRender;

public class SquareShapeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        SquareRender render = new SquareRender(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, render);
        setContentView(surfaceView);
    }
}