package com.rzm.opengles_doc;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.simple.TriangleShapeActivity;
import com.rzm.opengles_doc.simple.TriangleShapeActivity_with_Matrix;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static {
        System.loadLibrary("opengles");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    @Override
    public void onClick(View view) {
        int id = view.getId();
        Class clazz;
        if (id == R.id.btDraw2) {
            clazz = TriangleShapeActivity_with_Matrix.class;
        } else {
            clazz = TriangleShapeActivity.class;
        }
        startActivity(new Intent(this, clazz));
    }
}
