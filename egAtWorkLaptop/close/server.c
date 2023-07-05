#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <err.h>
#include <stdlib.h>

#define LOCALHOST "127.0.0.1"

int main(){
    //setup listener
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;
    setsockopt(serv, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    struct sockaddr_in sin;
    memset((char *)&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    //sin.sin_port = htons(1669);
    sin.sin_port = htons(1669);
    sin.sin_addr.s_addr = inet_addr(LOCALHOST);

    if (bind(serv,(struct sockaddr *)&sin, sizeof(sin)) < 0){
        err(EXIT_FAILURE, "bind for server failed");
    }

    if (listen(serv,1) < 0){
        err(EXIT_FAILURE, "listen for server failed");
    }
    printf("ready to call accept!\n");

    struct sockaddr_in clientSin;
    socklen_t clientAddeLen = sizeof(clientSin);
    memset((char *)&clientSin, 0, sizeof(clientSin));

    int client = accept(serv, (struct sockaddr *)&clientSin, &clientAddeLen);
    printf("got client!\n");

    while(1){
        int c = getchar();
        if (c == 'y') break;
    }

    close(client);
    close(serv);
}
