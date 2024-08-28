package com.rzm.opengles_doc.simple;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.R;
import com.rzm.opengles_doc.egl.EGLBackgroundRender;

public class EGLOutOfScreenDrawActivity extends AppCompatActivity {

    private EGLBackgroundRender render;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_egl_back_env);

        Bitmap bmp = BitmapFactory.decodeResource(getResources(), R.drawable.cat);
        int width = bmp.getWidth();
        int height = bmp.getHeight();
        render = new EGLBackgroundRender();
        render.init(bmp, width, height);
    }
}