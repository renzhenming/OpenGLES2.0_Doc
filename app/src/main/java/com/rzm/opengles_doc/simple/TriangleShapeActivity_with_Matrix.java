package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.TriangleRender;
import com.rzm.opengles_doc.render.TriangleRenderWithMatrix;

public class TriangleShapeActivity_with_Matrix extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TriangleRenderWithMatrix triangleRender = new TriangleRenderWithMatrix(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, triangleRender);
        setContentView(surfaceView);
    }
}