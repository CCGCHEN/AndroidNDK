#include <jni.h>
#include <string>

//空指针异常
void nullPointCrash() {
    int *p = NULL;
    *p = 1;
    printf("%d\n", *p);
    JNIEnv *env;
    if (env->ExceptionCheck() || env->ExceptionOccurred()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        jclass cls_exp = env->FindClass("java/lang/Exception");
        env->ThrowNew(cls_exp, "call java error");
    }

}

//野指针
void errorAddressCrash() {
    //没有分配地址
    int *p;
    //进行赋值
    *p = 1;
}

//数据越界
void arrayListOutBounds() {
    int data[10];
    data[11] = 11;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_canter_ndkdemo4_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    nullPointCrash();





    return env->NewStringUTF(hello.c_str());
}
