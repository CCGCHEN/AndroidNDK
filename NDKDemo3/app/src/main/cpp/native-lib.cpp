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



JNIEXPORT void JNICALL Java_com_canter_ndkdemo3_JNIMethod_callInstanceMethod__I
        (JNIEnv *env, jobject jobject1, jint jint1) {
    jclass clas_JNIMethod = env->FindClass("com/canter/ndkdemo3/JNIMethod");
    if (clas_JNIMethod == NULL) {
        return;
    }

    //找到对应的构造方法
    jmethodID  construct_Method = env->GetMethodID(clas_JNIMethod, "<init>", "()V");

    if (construct_Method == NULL) {
        return;
    }

    //创建对象
    jobject jniMethodObj = env->NewObject(clas_JNIMethod, construct_Method, NULL);

    if (jniMethodObj == NULL) {
        return;
    }

    //找到对应的实例
    jfieldID  jfieldID1 = env->GetFieldID(clas_JNIMethod, "address", "Ljava/lang/String;");
    if (jfieldID1 == NULL) {
        return;
    }

    jstring addressData = env->NewStringUTF("native call guangxi");
    //修改对应的实例
    env->SetObjectField(jniMethodObj, jfieldID1, addressData);

    //找到对应的实例方法方法
    jmethodID jmethodID1 = env->GetMethodID(clas_JNIMethod, "logAddress", "(Ljava/lang/String;)V");
    if (jmethodID1 == NULL) {
        return;
    }
    jstring address = env->NewStringUTF("call instance method");
    //调用对应的实例方法
    env->CallVoidMethod(jniMethodObj, jmethodID1, address);

    env->DeleteLocalRef(address);
    env->DeleteLocalRef(addressData);

}