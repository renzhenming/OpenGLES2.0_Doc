package com.rzm.opengles_doc.simple;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.CameraGlSurfaceView;
import com.rzm.opengles_doc.render.CameraRender;

public class CameraActivity extends AppCompatActivity {

    private CameraGlSurfaceView surfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        CameraRender render = new CameraRender(this);
        surfaceView = new CameraGlSurfaceView(this, render);
        setContentView(surfaceView);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        menu.add("切换摄像头").setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        surfaceView.switchCamera();
        return super.onOptionsItemSelected(item);
    }
}