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

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class MainGLES3Activity extends AppCompatActivity implements GLViewAdapter.OnItemClickListener {

    public static final int IMAGE_FORMAT_RGBA = 0x01;
    public static final int IMAGE_FORMAT_NV21 = 0x02;
    private ViewGroup mRootView;
    private MyGlSurfaceView mGLSurfaceView;
    private JavaGLRender mGLRender;
    private static final String[] ITEM_TITLES = {"绘制三角形", "纹理贴图", "YUV纹理贴图", "VAO VBO绘制正方形"};
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

        try {
            setImageDataToNative(renderType);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        mGLSurfaceView.requestRender();
        mRenderDialog.cancel();
    }

    public void setImageDataToNative(int renderType) throws IOException {
        switch (renderType) {
            case NativeRender.TYPE_TRIANGLE:
                break;
            case NativeRender.TYPE_TEXTURE_MAP:
                InputStream is = this.getAssets().open("girl.jpg");
                Bitmap bitmap = BitmapFactory.decodeStream(is);
                int bytes = bitmap.getByteCount();
                ByteBuffer buf = ByteBuffer.allocate(bytes);
                bitmap.copyPixelsToBuffer(buf);
                byte[] byteArray = buf.array();
                mGLRender.setImage(IMAGE_FORMAT_RGBA, bitmap.getWidth(), bitmap.getHeight(), byteArray);
                break;
            case NativeRender.TYPE_YUV_TEXTURE_MAP:
                is = this.getAssets().open("YUV_Image_840x1074.NV21");
                int length = is.available();
                byte[] buffer = new byte[length];
                is.read(buffer);
                mGLRender.setImage(IMAGE_FORMAT_NV21, 840, 1074, buffer);
                break;
            case NativeRender.TYPE_VAO:
                break;
        }
    }
}
