package com.rzm.opengles_doc.gles3;

import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.rzm.opengles_doc.R;

import java.util.List;

public class GLViewAdapter extends RecyclerView.Adapter<GLViewAdapter.GLViewHolder> implements View.OnClickListener {
    private List<String> mTitles;
    private int mSelectIndex = 0;
    private OnItemClickListener mOnItemClickListener = null;

    public GLViewAdapter(@NonNull List<String> titles) {
        mTitles = titles;
    }

    public void setSelectIndex(int index) {
        mSelectIndex = index;
    }

    public int getSelectIndex() {
        return mSelectIndex;
    }

    public void setOnItemClickListener(OnItemClickListener onItemClickListener) {
        mOnItemClickListener = onItemClickListener;
    }

    @NonNull
    @Override
    public GLViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.gles3_item, parent, false);
        GLViewHolder holder = new GLViewHolder(view);
        view.setOnClickListener(this);
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull GLViewHolder holder, int position) {
        if (position == mSelectIndex) {
            holder.mTitle.setTextColor(Color.RED);
        } else {
            holder.mTitle.setTextColor(Color.GRAY);
        }
        holder.mTitle.setText(mTitles.get(position));
        holder.itemView.setTag(position);
    }

    @Override
    public int getItemCount() {
        return mTitles.size();
    }

    @Override
    public void onClick(View v) {
        if (mOnItemClickListener != null) {
            mOnItemClickListener.onItemClick(v, (Integer) v.getTag());
        }
    }

    public interface OnItemClickListener {
        void onItemClick(View view, int position);
    }

    class GLViewHolder extends RecyclerView.ViewHolder {
        TextView mTitle;

        public GLViewHolder(View itemView) {
            super(itemView);
            mTitle = itemView.findViewById(R.id.item_title);
        }
    }
}