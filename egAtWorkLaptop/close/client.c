#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <err.h>
#include <stdlib.h>

//#define LOCALHOST "127.0.0.1"
#define LOCALHOST "6.9.6.9"
int main(){
    int client = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sin;
    memset((char *)&sin, 0, sizeof(sin));

    /*
    sin.sin_family = AF_INET;
    //sin.sin_port = htons(1669);
    sin.sin_port = htons(5556);
    sin.sin_addr.s_addr = inet_addr(LOCALHOST);

    if (bind(client,(struct sockaddr *)&sin, sizeof(sin)) < 0){
        err(EXIT_FAILURE, "bind for client failed");
    }
    */

    sin.sin_family = AF_INET;
    //sin.sin_port = htons(1669);
    sin.sin_port = htons(1669);
    sin.sin_addr.s_addr = inet_addr(LOCALHOST);

    if (connect(client,(struct sockaddr *)&sin, sizeof(sin) ) < 0){
        err(EXIT_FAILURE, "connect for client failed");
    }

    while(1){
        int c = getchar();
        if (c == 'y') break;
    }
    close(client);
}
