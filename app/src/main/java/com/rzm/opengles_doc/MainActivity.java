package com.rzm.opengles_doc;

import android.Manifest;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import com.rzm.opengles_doc.simple.BlendColorActivity;
import com.rzm.opengles_doc.simple.BlurTextureImageActivity;
import com.rzm.opengles_doc.simple.CameraActivity;
import com.rzm.opengles_doc.simple.CoolTextureImageActivity;
import com.rzm.opengles_doc.simple.CubeShapeActivity;
import com.rzm.opengles_doc.simple.CubeTransformActivity;
import com.rzm.opengles_doc.simple.EGLOutOfScreenDrawActivity;
import com.rzm.opengles_doc.simple.EtcCompressedTextureActivity;
import com.rzm.opengles_doc.simple.FboOutOfScreenDrawActivity;
import com.rzm.opengles_doc.simple.GrayTextureImageActivity;
import com.rzm.opengles_doc.simple.MagnifierTextureImageActivity;
import com.rzm.opengles_doc.simple.SquareShapeActivity;
import com.rzm.opengles_doc.simple.TextureImageActivity;
import com.rzm.opengles_doc.simple.TriangleShapeActivity;
import com.rzm.opengles_doc.simple.TriangleShapeActivity_with_Matrix;
import com.rzm.opengles_doc.simple.WarmTextureImageActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static {
        System.loadLibrary("opengles");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
    }

    @Override
    public void onClick(View view) {
        int id = view.getId();
        Class clazz;
        if (id == R.id.btDraw2) {
            clazz = TriangleShapeActivity_with_Matrix.class;
        } else if (id == R.id.square) {
            clazz = SquareShapeActivity.class;
        } else if (id == R.id.cube) {
            clazz = CubeShapeActivity.class;
        } else if (id == R.id.image) {
            clazz = TextureImageActivity.class;
        } else if (id == R.id.gray) {
            clazz = GrayTextureImageActivity.class;
        } else if (id == R.id.cool) {
            clazz = CoolTextureImageActivity.class;
        } else if (id == R.id.warm) {
            clazz = WarmTextureImageActivity.class;
        } else if (id == R.id.magnifier) {
            clazz = MagnifierTextureImageActivity.class;
        } else if (id == R.id.blur) {
            clazz = BlurTextureImageActivity.class;
        } else if (id == R.id.transform) {
            clazz = CubeTransformActivity.class;
        } else if (id == R.id.camera) {
            clazz = CameraActivity.class;
        } else if (id == R.id.egl) {
            clazz = EGLOutOfScreenDrawActivity.class;
        } else if (id == R.id.fbo) {
            clazz = FboOutOfScreenDrawActivity.class;
        } else if (id == R.id.etc) {
            clazz = EtcCompressedTextureActivity.class;
        } else if (id == R.id.blend) {
            clazz = BlendColorActivity.class;
        } else {
            clazz = TriangleShapeActivity.class;
        }
        startActivity(new Intent(this, clazz));
    }
}
