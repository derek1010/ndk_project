#include <jni.h>
#include <string>

#include <stdio.h>

#include <signal.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <sys/resource.h>

#include <android/log.h>

#define  LOG_TAG    "derek"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)




static int signal_write_fd = -1;
static int signal_read_fd = -1;
static int epoll_fd = -1;
static void SIGCHLD_handler(int k);

extern "C"

jstring
Java_com_example_derek_csample1117_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    int i = 1;
    struct rlimit rl;
    rl.rlim_cur = RLIM_INFINITY;
    rl.rlim_max= RLIM_INFINITY;
    if(setrlimit(RLIMIT_CORE, &rl)== -1){
        LOGD("set RLIMIT failed\n");
    }else
        LOGD("set RLIMIT successful \n");


    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"

jstring
Java_com_example_derek_csample1117_MainActivity_coreDump(
        JNIEnv* env,
        jobject /* this */) {

    //char *a = NULL ;
    //*a = 0x323;

    std::string hello = "return from coredump()";
    return env->NewStringUTF(hello.c_str());


}

extern "C"

jstring
Java_com_example_derek_csample1117_MainActivity_fork(
        JNIEnv* env,
        jobject /* this */) {

     fork();
     fork();
    std::string hello = "return from fork()";
    return env->NewStringUTF(hello.c_str());


}



extern "C"


//it seems the signalhandler is not working in NDK, but the crash didn't happend also.
jstring
Java_com_example_derek_csample1117_MainActivity_sighandlerRegister(
        JNIEnv* env,
        jobject /* this */) {

    // Write to signal_write_fd if we catch SIGCHLD.
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = SIGCHLD_handler;
    act.sa_flags = SA_RESTART | SA_SIGINFO | SA_NOCLDSTOP;
    sigaction(SIGABRT, &act, 0);
    sigaction(SIGSEGV, &act, 0);

    std::string hello = "return from handlerRegister()";
    return env->NewStringUTF(hello.c_str());

}

static void SIGCHLD_handler(int k) {

    LOGD("derek , child process dead k= %d\n", k);
   // if (TEMP_FAILURE_RETRY(write(signal_write_fd, &k, sizeof(k))) == -1) {
   //     LOGD("write(signal_write_fd) failed: %s\n", strerror(errno));
   // }
}

