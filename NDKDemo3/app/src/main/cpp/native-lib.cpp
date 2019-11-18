#include <jni.h>
#include <string>
#include "com_canter_ndkdemo3_JNIMethod.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_canter_ndkdemo3_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


JNIEXPORT void JNICALL Java_com_canter_ndkdemo3_JNIMethod_callStaticMethod__I
        (JNIEnv *env, jclass jclass1, jint jint1) {
    //找到对应的类，需要全路径。将"." 替换成 "/"
    jclass clas_JNIMethod = env->FindClass("com/canter/ndkdemo3/JNIMethod");
    if (clas_JNIMethod==NULL) {
        return;
    }
    //获取对应的方法，静态和实例方法调用的是不同的api
    jmethodID method_StaticMethodId =  env->GetStaticMethodID(clas_JNIMethod, "staticMethod",
            "(Ljava/lang/String;)V");

    if (method_StaticMethodId == NULL) {
        return;
    }

    jstring data = env->NewStringUTF(" call static method");

    if (data == NULL) {
        return;
    }
    //调用相关方法
    env->CallStaticVoidMethod(clas_JNIMethod, method_StaticMethodId, data);


    //调用静态变量
    jfieldID  jfieldID1 = env->GetStaticFieldID(jclass1, "sData", "Ljava/lang/String;");
    if (jfieldID1 == NULL) {
        return;
    }

    jstring  jstring1 = env->NewStringUTF("native-lib");
    //更改值
    env->SetStaticObjectField(jclass1, jfieldID1, jstring1);
    env->CallStaticVoidMethod(clas_JNIMethod, method_StaticMethodId, data);

    //释放相关的资源
    env->DeleteLocalRef(clas_JNIMethod);
    env->DeleteLocalRef(data);

    env->DeleteLocalRef(jstring1);
}

