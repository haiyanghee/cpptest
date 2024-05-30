/*
   Wanna see if child close write end of pipe but parent don't, does read return EOF?
   I expect no because the fd is not actually closed when all of the "references" open to it are closed

OK: each process have a list of fd, so if you close the fd in the process, even if the actual underlying file is not closed, if you use the closed fd its bad.. you'll get bad fd if no new fd used the same fd as the old fd value
for read(), it will return EOF when the actual underlying file gets closed..
for write(), it will error when the actual underlying file gets closed..
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <err.h>
#include <errno.h>
#include <signal.h>

int main(){
    //block sigpipe..
    {
        signal(SIGPIPE, SIG_IGN); //this is ignore sigpipe, not "block", although this still makes write() returns EPIPE..

        //blocking signal means temporarily block.. if you always want to "block"  it , should just ignore it
        //https://www.gnu.org/software/libc/manual/html_node/Blocking-Signals.html
        //https://stackoverflow.com/questions/5730975/difference-in-handling-of-signals-in-unix
        /*
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGPIPE);
        pthread_sigmask(SIG_BLOCK, &set, NULL);
        */
    }


    int socks[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0,socks) != 0) {err(EXIT_FAILURE, NULL);}

    int pid = fork();
    if (pid == 0){
        //child
        //sleep(1);
        printf("child !\n");

        close(socks[1]);
        ssize_t wr=0;
        wr = write(socks[0],"abcd",sizeof("abcd"));
         if ( wr == -1){//don't write to sock[0] if parent is listening on sock[0]..
             warn("child write errored!");
         }
        printf("child wr = %ld\n", wr);
        //write(socks[1],"a",1); //write to sock[1] instead

        /*
        close(socks[0]);


        char buf[2]={-1};
        //size_t rLen = read(socks[0],buf,1);
        ssize_t rLen = read(socks[1],buf,1);
        if (rLen == -1) { warn("child read returned error!"); }
        printf("child rLen = %ld, buf[0] = %d\n", rLen, buf[0]);
        */



        sleep(2);

        printf("child closing!\n");
        exit(0);//should close sockets
    }
    //parent will read
    //parent will close the "write end"
    //if parent don't close the "write end", it's still considered open since child/parent refers to same underlying fd, which 2 references
    close(socks[1]);
    close(socks[0]);



    /*
    char buf[2]={-1};
    //size_t rLen = read(socks[0],buf,1);
    ssize_t rLen = read(socks[1],buf,1);
    if (rLen == -1) { warn("parent read returned error!"); }
    printf("parent rLen = %ld, buf[0] = %d\n", rLen, buf[0]);
    */
}
