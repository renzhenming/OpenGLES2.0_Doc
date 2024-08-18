package com.rzm.opengles_doc;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.rzm.opengles_doc.simple.SimpleShapeActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    @Override
    public void onClick(View view) {
        int id = view.getId();
        Class clazz = SimpleShapeActivity.class;
        startActivity(new Intent(this, clazz));
    }
}
