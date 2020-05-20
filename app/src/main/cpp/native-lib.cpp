#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "Camera2Demo", __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL Java_com_example_camera_JNIUtils_JNIRGBADisplay(
        JNIEnv *env, jclass obj, jobject src, jint srcWidth, jint srcHeight, jobject surface) {

    uint8_t *srcPtr = reinterpret_cast<uint8_t *>(env->GetDirectBufferAddress(src));

    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    ANativeWindow_acquire(window);
    ANativeWindow_Buffer buffer;
    //set output size and format
    //only 3 formats are available: WINDOW_FORMAT_RGBA_8888(DEFAULT), WINDOW_FORMAT_RGBX_8888, WINDOW_FORMAT_RGB_565
    ANativeWindow_setBuffersGeometry(window, 0, 0, WINDOW_FORMAT_RGBA_8888);
    if (int32_t err = ANativeWindow_lock(window, &buffer, NULL)) {
        LOGE("ANativeWindow_lock failed with error code: %d\n", err);
        ANativeWindow_release(window);
    }

    size_t rowStride = sizeof(uint8_t) * srcWidth;
    uint8_t * outPtr = reinterpret_cast<uint8_t *>(buffer.bits);
    uint8_t *yPtr = srcPtr;
    uint8_t R = 0, G = 0, B = 0, Y = 0;
    for (size_t y = 0; y < srcHeight; y++) {
        yPtr += rowStride;

        for (size_t x = 0; x < srcWidth; x++) {
            Y = yPtr[x];
            //Y = (yPtr[x] & 0x80)? 255: 0;
            R = Y;
            G = Y;
            B = Y;

            *outPtr++ = R;
            *outPtr++ = G;
            *outPtr++ = B;
            *outPtr++ = 255;
        }
    }

    ANativeWindow_unlockAndPost(window);
    ANativeWindow_release(window);
}