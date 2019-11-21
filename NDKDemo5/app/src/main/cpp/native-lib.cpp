#include <jni.h>
#include <string>
#include <stdlib.h>
#include<android/log.h>

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "ndk_demo5_native", __VA_ARGS__)

jmethodID getNameID;
jfieldID ifild;
jclass mainActivity;

//調用Java方法
void callJava(JNIEnv *env, jobject obj) {
    mainActivity = env->GetObjectClass(obj);
    getNameID = env->GetMethodID(mainActivity, "getMainData", "()V");
    env->CallVoidMethod(obj, getNameID);
}

//获取Java全局变量
void getFild(JNIEnv *env, jobject obj) {
    ifild = env->GetFieldID(mainActivity, "java_field", "I");
    jint fid = env->GetIntField(obj, ifild);
    LOGV("从Java层获取到的java_field变量的值是：%d", fid);
    LOGV("修改java_field的值为99");
    env->SetIntField(obj, ifild, 99); //修改变量的值

}

extern "C" JNIEXPORT jstring JNICALL
Java_com_canter_ndkdemo5_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject obj) {
    std::string hello = "Hello from C++";

    callJava(env, obj);
    getFild(env, obj);

    return env->NewStringUTF(hello.c_str());
}


//替换java端的testVoid
void native_void() {
    LOGV("调用了native_void，是java 层对应的testVoid方法");
}


//替换java端的testInt
int native_testInt() {
    return 200;
}

//注册Java端的方法  以及本地相对应的方法
JNINativeMethod method[] = {{"testVoid", "()V", (void *) native_void},
                            {"testInt",  "()I", (int *) native_testInt}};

//注册相应的类以及方法
jint registerNativeMeth(JNIEnv *env) {
    jclass cl = env->FindClass("com/canter/ndkdemo5/MainActivity");
    if ((env->RegisterNatives(cl, method, sizeof(method) / sizeof(method[0]))) < 0) {
        return -1;
    }
    return 0;
}

//实现jni_onload 动态注册方法
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    if (registerNativeMeth(env) != JNI_OK) {//注册方法
        return -1;
    }
    return JNI_VERSION_1_4;//必须返回这个值
}