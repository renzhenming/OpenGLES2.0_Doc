package com.rzm.opengles_doc.simple;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.EtcRender;

import java.io.IOException;

public class EtcCompressedTextureActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        try {
            EtcRender render = new EtcRender(this);
            MyGlSurfaceView surfaceView = new MyGlSurfaceView(this, render);
            render.setGlSurfaceView(surfaceView);
            setContentView(surfaceView);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}