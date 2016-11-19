
//
// Created by 大可 on 2016/11/19.
//

#include <jni.h>
#include <string>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

#include <android/log.h>

#define  LOG_TAG    "derek"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


static int mainfunction();

extern "C"

jstring
Java_com_example_derek_csample1117_MainActivity_threadtest(
        JNIEnv* env,
        jobject /* this */) {

    mainfunction();
    std::string hello = "return from threadtest()";
    return env->NewStringUTF(hello.c_str());


}




pthread_mutex_t cntr_mutex = PTHREAD_MUTEX_INITIALIZER;

long protVariable = 0L;

void *myThread(void *arg)
{
    int i, ret;
    for (i=0; i<10000;i++){
        ret = pthread_mutex_lock(&cntr_mutex);
        assert(ret==0);
        protVariable ++;
        ret = pthread_mutex_unlock( &cntr_mutex);
        assert(ret==0);

    }
    pthread_exit(NULL);
}


#define MAX_THREADS 10


int mainfunction()
{
    int ret, i ;
    pthread_t threadIds[MAX_THREADS];
    for(i=0;i< MAX_THREADS; i ++) {
        ret= pthread_create(& threadIds[i], NULL, myThread, NULL);
        if(ret != 0){
            LOGE("Error creating thread %d \n", (int) threadIds[i]);
        }

    }
    for(i=0; i< MAX_THREADS; i ++) {
        LOGD(" before join thread %d \n", (int)threadIds[i]);
        ret = pthread_join(threadIds[i], NULL);
        if(ret != 0)
            LOGE("Error joining thread %d \n", (int)threadIds[i]);

        LOGD(" after join thread %d \n", (int)threadIds[i]);
    }

    LOGD("derek The protected variable value is %d\n", protVariable);
    ret = pthread_mutex_destroy( &cntr_mutex);
    if(ret != 0)
        LOGD(" Couldn't destroy the mutex \n ");
    return 0;


}

