#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

bool gb=true;
void sighandler(int signo){
    gb=false;
    printf("in sighandler with signo %d\n", signo);
}

void setHandler(int signo){
    struct sigaction sa;
    //always use the same signal handler as eg
    sa.sa_handler = sighandler;
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
    setHandler(SIGINT);
}
int main(){
    setSigHandlers();
    while (gb){
        printf("in loop!\n");
        const unsigned int a =sleep(3);
        printf("a = %d\n", a);
    }
    printf("out of loop!\n");
}
