package com.rzm.opengles_doc.simple;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.MyGlSurfaceView;
import com.rzm.opengles_doc.render.CameraRender;

public class CameraActivity extends AppCompatActivity {

    private MyGlSurfaceView surfaceView;
    private CameraRender render;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        render = new CameraRender(this);
        surfaceView = new MyGlSurfaceView(this, render);
        render.bindSurfaceView(surfaceView);
        setContentView(surfaceView);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        menu.add("切换摄像头").setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        render.switchCamera();
        return super.onOptionsItemSelected(item);
    }
}