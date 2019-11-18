package com.canter.ndkdemo3;

import android.util.Log;

/**
 * Description :
 * Creation    : 2019/11/18
 * Author      : cangui.ccg
 */
public class JNIMethod {

    public static String sData = "JNIMethod";

    public static native void callStaticMethod(int i);

    public static native void callStaticMethod(int i, String str);

    public native void callInstanceMethod(int i);

    public native void callInstanceMethod(String str, long i);


    public static void logMessage(String data) {
        Log.d("tag", sData + data);
    }

    public static void staticMethod(String data) {
        logMessage(data);
    }
}
