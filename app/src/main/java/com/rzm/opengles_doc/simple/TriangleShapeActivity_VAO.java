package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.TriangleRenderWithMatrix_VAO;
import com.rzm.opengles_doc.render.TriangleRenderWithMatrix_VBO_EBO;

public class TriangleShapeActivity_VAO extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TriangleRenderWithMatrix_VAO triangleRender = new TriangleRenderWithMatrix_VAO(this);
        MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, triangleRender);
        setContentView(surfaceView);
    }
}