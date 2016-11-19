//
// Created by 大可 on 2016/11/19.
//

#include <jni.h>
#include <string>


extern "C"

jstring
Java_com_example_derek_csample1117_MainActivity_sockettest(
        JNIEnv* env,
        jobject /* this */) {

    std::string hello = "return from sockettest()";
    return env->NewStringUTF(hello.c_str());


}