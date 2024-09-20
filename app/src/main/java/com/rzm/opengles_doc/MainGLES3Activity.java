package com.rzm.opengles_doc;

import static android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY;

import android.app.AlertDialog;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.rzm.opengles_doc.gles3.GLViewAdapter;
import com.rzm.opengles_doc.gles3.JavaGLRender;
import com.rzm.opengles_doc.gles3.NativeRender;

import java.io.InputStream;
import java.lang.reflect.Type;
import java.util.Arrays;

public class MainGLES3Activity extends AppCompatActivity implements GLViewAdapter.OnItemClickListener {

    private ViewGroup mRootView;
    private MyGlSurfaceView mGLSurfaceView;
    private JavaGLRender mGLRender;
    private static final String[] ITEM_TITLES = {"绘制三角形", "纹理贴图"};
    private AlertDialog mRenderDialog;
    private GLViewAdapter mRenderAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gles3_main);
        mRootView = (ViewGroup) findViewById(R.id.rootView);
        mGLRender = new JavaGLRender();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.menu_item) {
            showGLSampleDialog();
        }
        return true;
    }

    private void showGLSampleDialog() {
        mRenderDialog = new AlertDialog.Builder(this).create();
        LayoutInflater inflater = LayoutInflater.from(this);
        final View rootView = inflater.inflate(R.layout.gles3_list, null);
        final RecyclerView listView = rootView.findViewById(R.id.list_view);
        mRenderAdapter = new GLViewAdapter(Arrays.asList(ITEM_TITLES));
        mRenderAdapter.setSelectIndex(0);
        mRenderAdapter.setOnItemClickListener(this);
        LinearLayoutManager manager = new LinearLayoutManager(this);
        manager.setOrientation(LinearLayoutManager.VERTICAL);
        listView.setLayoutManager(manager);
        listView.setAdapter(mRenderAdapter);
        mRenderDialog.show();
        mRenderDialog.setContentView(rootView);
    }

    public void onItemClick(View view, int position) {
        mRootView.removeView(mGLSurfaceView);
        ViewGroup.LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        mGLSurfaceView = new MyGlSurfaceView(MainGLES3Activity.this, mGLRender);
        mRootView.addView(mGLSurfaceView, params);
        int selectIndex = mRenderAdapter.getSelectIndex();
        mRenderAdapter.setSelectIndex(position);
        mRenderAdapter.notifyItemChanged(selectIndex);
        mRenderAdapter.notifyItemChanged(position);
        mGLSurfaceView.setRenderMode(RENDERMODE_WHEN_DIRTY);
        mGLSurfaceView.setRatio(mGLSurfaceView.getWidth(), mGLSurfaceView.getHeight());
        int renderType = NativeRender.TYPE + position;
        mGLRender.setRenderType(renderType);

        switch (renderType) {
            case NativeRender.TYPE_TRIANGLE:
                break;
            case NativeRender.TYPE_TEXTURE_MAP:
                Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.girl);
                mGLRender.setImage(bitmap);
                break;
        }

        mGLSurfaceView.requestRender();
        mRenderDialog.cancel();
    }
}
