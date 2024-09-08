package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.TriangleRenderWithMatrix;
import com.rzm.opengles_doc.render.TriangleRenderWithMatrix_VBO_EBO;

public class TriangleShapeActivity_VBO_EBO extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TriangleRenderWithMatrix_VBO_EBO triangleRender = new TriangleRenderWithMatrix_VBO_EBO(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, triangleRender);
        setContentView(surfaceView);
    }
}