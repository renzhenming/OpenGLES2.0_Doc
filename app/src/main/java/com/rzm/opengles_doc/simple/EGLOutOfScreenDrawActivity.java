package com.rzm.opengles_doc.simple;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.R;
import com.rzm.opengles_doc.egl.EGLBackgroundRender;

public class EGLOutOfScreenDrawActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_egl_back_env);
        ImageView imageView = findViewById(R.id.mImage);
        Bitmap bmp = BitmapFactory.decodeResource(getResources(), R.drawable.cat);
        int width = bmp.getWidth();
        int height = bmp.getHeight();
        EGLBackgroundRender render = new EGLBackgroundRender(this);
        render.init(bmp, width, height);
        Bitmap draw = render.draw();
        if (draw != null) {
            imageView.setImageBitmap(draw);
        }
    }
}