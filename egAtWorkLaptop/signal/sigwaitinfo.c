#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

bool gotSIGINT, gotSIGALRM;

void sigintHandler(int ){ gotSIGINT=true; }
void sigalrmHandler(int ){ gotSIGALRM=true; }

void setHandler(int signo, void (*handler)(int signo)){
    struct sigaction sa;
    //always use the same signal handler as eg
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;//no flags 
    if (sigaction(signo, &sa, NULL) == -1){
        printf("Cannot sigaction!\n");
        exit(EXIT_FAILURE);
    }
}

void setSigHandlers(){
    //ignore SIGHUP and SIGPIPE
    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    //add handlers
    setHandler(SIGINT, sigintHandler);
    setHandler(SIGALRM, sigalrmHandler);
}
int main(){
    setSigHandlers();
    sigset_t sigSet, oldSigSet;
    sigemptyset(&sigSet);
    //sigaddset(&sigSet, SIGALRM); //only wait for SIGALRM
    sigaddset(&sigSet, SIGINT); //only wait for SIGINT

    //TODO: need to block set?
    //pthread_sigmask(SIG_BLOCK, &sigSet, &oldSigSet);


    siginfo_t sigInfoOut = {0};
    //int ret = sigwaitinfo(&sigSet, &sigInfoOut);
    struct timespec timeoutSpec= {0};
    timeoutSpec.tv_sec=2;
    int ret = sigtimedwait(&sigSet, &sigInfoOut, &timeoutSpec);
    if (ret == -1){
        int prevErrno = errno;
        if (prevErrno == EINTR){
            printf("got EINTR, so some other unblocked signal not in sigSet came!\n");
        } else if (prevErrno == EAGAIN){
            printf("got EAGAIN, so we timed out and no signal came in the time period %ldsec %ldns!\n", timeoutSpec.tv_sec,timeoutSpec.tv_nsec);
        }
        printf("err: %s\n", strerror(prevErrno));
    }
    else {
        printf("successfully waited for signal %d!\n",ret);
    }

    //print siginfo
    printf("printing siginfo..\n");
    printf("siginfo.si_signo = %d\n", sigInfoOut.si_signo);
    printf("siginfo.si_code = %d\n", sigInfoOut.si_code);
    printf("siginfo.si_pid = %d\n", sigInfoOut.si_pid);
    printf("siginfo.si_uid = %d\n", sigInfoOut.si_uid);
    printf("siginfo.si_status = %d\n", sigInfoOut.si_status);

    printf("gotSIGINT = %d, gotSIGALRM = %d\n", gotSIGINT, gotSIGALRM);
    gotSIGINT = gotSIGALRM = false;
    sleep(3);
    printf("gotSIGINT = %d, gotSIGALRM = %d\n", gotSIGINT, gotSIGALRM);
    
}
