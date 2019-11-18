package com.canter.ndkdemo2.ndk;


import android.graphics.Bitmap;

/**
 * Description :
 * Creation    : 2019/11/10
 * Author      : cangui.ccg
 */
public class JniData {
    public static native String getDataFromJni();

    public static native String setJavaFromJava();

    public static native Bitmap getBitmapFromJni();
}
