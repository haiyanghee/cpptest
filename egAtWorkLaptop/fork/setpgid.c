#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <err.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    int pid = fork();
    if (pid ==0 ){
        //get new pgid
        setpgid(0,0);
        printf("in child's pid = %d, pgid = %d, pgid? = %d\n", getpid(), getpgid(0), getpgid(getpid()));
        //sleep(69);
        printf("child exiting \n"); exit(0);
    }
    //sleep(1);
    printf("in parent's pid = %d, child's pid = %d, child's pgid = %d \n", getpid(),pid, getpgid(pid));
    printf("in parent: child's pgid = %d\n", getpgid(pid));
    sleep(69);
    wait(NULL);
}
