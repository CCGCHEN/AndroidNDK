#include <jni.h>
#include <string>
#include <head/com_canter_ndkdemo2_ndk_JniData.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_canter_ndkdemo2_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
