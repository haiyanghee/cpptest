// clang-format off
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int fds[2];
    pipe(fds);
    close(2);
    printf("%d\n", dup(fds[0]));
    printf("%d\n",fds[0]);
}
