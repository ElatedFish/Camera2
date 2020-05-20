package com.example.camera;

import android.graphics.ImageFormat;
import android.media.Image;
import android.view.Surface;

import java.nio.ByteBuffer;


public class JNIUtils {
    // TAG for JNIUtils class
    private static final String TAG = "JNIUtils";

    // Load native library.
    static {
        System.loadLibrary("native-lib");
    }

    public static native void JNIRGBADisplay(ByteBuffer image, int srcWidth, int srcHeight, Surface surface);

    public static void RGBADisplay(Image image, Surface surface) {
        if (image.getFormat() != ImageFormat.YUV_420_888) {
            //throw new IllegalAccessException("source image must be format YUV_420_888");
            return;
        }

        Image.Plane[] planes = image.getPlanes();

        JNIRGBADisplay(planes[0].getBuffer(), image.getWidth(), image.getHeight(), surface);
    };
}
