package com.canter.ndkdemo5;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "ndk_demo5_java";

    private int java_field = 100;
    private String name;


    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        Log.i(TAG,"testInt 获取结果  " + testInt());
        Log.i(TAG,"java_field 被修改完的值是  " + java_field);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public void getMainData() {
        Log.i(TAG, "调用了getMainData()");
        testVoid();
    }

    public native void testVoid();

    public native int testInt();

}
