#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define SA struct sockaddr
#define SERVER_PORT 6969
#define CLIENT_PORT 6970

int main(){
    int udpsoc = socket(AF_INET, SOCK_DGRAM, 0);
    const int TRUE = 1, FALSE=0;
    setsockopt(udpsoc, SOL_SOCKET, SO_REUSEADDR, &TRUE, sizeof(TRUE));

    int size=0;
    socklen_t sizeOfInt=sizeof(size);
    getsockopt(udpsoc, SOL_SOCKET, SO_SNDBUF, &size, &sizeOfInt);
    printf("udp's SO_SNDBUF = %d\n", size);

    //man netdevice
    struct ifreq ifr;
    //sadly I don't think there's an easy and portable way to get the interface for a socket..
    //const char* in = "wlp0s20f3";
    const char* in = "vpn0";
    memcpy(ifr.ifr_ifrn.ifrn_name, in, MIN(strlen(in), sizeof(ifr.ifr_ifrn.ifrn_name)));
    ioctl(udpsoc, SIOCGIFMTU, &ifr);
    printf("udp's MTU = %d, interface name = %s\n", ifr.ifr_ifru.ifru_mtu, ifr.ifr_ifrn.ifrn_name);
    const int mtu = ifr.ifr_ifru.ifru_mtu;

    {
        int segStat=0;
        getsockopt(udpsoc, SOL_SOCKET, UDP_SEGMENT, &segStat, &sizeOfInt);
        printf("udp have segment = %d\n", segStat);
        //setsockopt(udpsoc, SOL_SOCKET, UDP_SEGMENT, &FALSE, sizeof(FALSE));
    }
    

    struct sockaddr_in client={0}, server={0};
    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_port=htons(CLIENT_PORT);
    if (bind(udpsoc, (SA*) &client, sizeof(client)) != 0) err(EXIT_FAILURE, "could not bind client to IP = INADDR_ANY, port = %d!", CLIENT_PORT);

    {
    //const char* IPstr="127.0.0.1";
    const char* IPstr="10.0.181.28";
    //server.sin_addr.s_addr=INADDR_ANY;
    if (inet_pton(AF_INET, IPstr, &server.sin_addr) != 1) err(EXIT_FAILURE, "server IP = %s is invalid!", IPstr);
    server.sin_port=htons(SERVER_PORT);
    }

    int sentToRet;
    //char buf[]="123456789";
    //const size_t bytesOfInput=sizeof(buf) - 1;

    //int mallocSize=size+1;
    //int mallocSize=size;
    //const size_t bytesOfInput=(size_t)size-69;
    //const size_t bytesOfInput=(size_t)size-200000;
    //const size_t bytesOfInput=(size_t)size-150000;
    //const size_t bytesOfInput=(1<<16)-29;

    //default udp_rmem_min is 4096
    //const size_t bytesOfInput=4096+6900;
    //const size_t bytesOfInput=4096*2;
    //const size_t bytesOfInput=(size_t)mtu;
    const size_t bytesOfInput=(size_t)400;
    char* buf = malloc(bytesOfInput);
    {
        printf("will try to send %zu bytes\n", bytesOfInput);
        const int bytesSent = sentToRet = sendto(udpsoc, buf, bytesOfInput, 0, (SA*)&server, sizeof(server));
        printf("sendto returned %d\n", bytesSent);
        if (bytesSent == -1){
            err(EXIT_FAILURE,"sendto returned %d! something went wrong!\n", sentToRet);
        }
    }
    //sendmsg();
    //printf("sent %d data?\n", bytesOfInput);
}
