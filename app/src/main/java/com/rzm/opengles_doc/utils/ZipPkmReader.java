package com.rzm.opengles_doc.utils;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.ETC1;
import android.opengl.ETC1Util;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ZipPkmReader {

    private final String mPath;
    private ZipInputStream mZipStream;
    private AssetManager mManager;
    private ByteBuffer headerBuffer;

    public ZipPkmReader(Context context, String path) throws IOException {
        this.mManager = context.getAssets();
        this.mPath = path;
        this.mZipStream = new ZipInputStream(mManager.open(mPath));
    }

    public ETC1Util.ETC1Texture getNextTexture() throws IOException {
        if (mZipStream.getNextEntry() == null) {
            return null;
        }
        return createTexture(mZipStream);
    }

    private ETC1Util.ETC1Texture createTexture(InputStream input) throws IOException {
        byte[] ioBuffer = new byte[4096];
        if (input.read(ioBuffer, 0, ETC1.ETC_PKM_HEADER_SIZE) != ETC1.ETC_PKM_HEADER_SIZE) {
            throw new IOException("read pkm file header fail.");
        }
        if (headerBuffer == null) {
            headerBuffer = ByteBuffer.allocateDirect(ETC1.ETC_PKM_HEADER_SIZE).order(ByteOrder.nativeOrder());
        }
        headerBuffer.put(ioBuffer, 0, ETC1.ETC_PKM_HEADER_SIZE).position(0);
        if (!ETC1.isValid(headerBuffer)) {
            throw new IOException("pkm format wrong.");
        }
        int width = ETC1.getWidth(headerBuffer);
        int height = ETC1.getHeight(headerBuffer);
        int encodedSize = ETC1.getEncodedDataSize(width, height);
        ByteBuffer dataBuffer = ByteBuffer.allocateDirect(encodedSize).order(ByteOrder.nativeOrder());
        int len;
        while ((len = input.read(ioBuffer)) != -1) {
            dataBuffer.put(ioBuffer, 0, len);
        }
        dataBuffer.position(0);
        return new ETC1Util.ETC1Texture(width, height, dataBuffer);
    }

    public void close() throws IOException {
        if (mZipStream != null) {
            mZipStream.closeEntry();
            mZipStream.close();
        }
        if (headerBuffer != null) {
            headerBuffer.clear();
            headerBuffer = null;
        }
    }
}
