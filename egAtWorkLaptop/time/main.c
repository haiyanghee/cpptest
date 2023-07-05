// clang-format off
#include <stdio.h>
#include <unistd.h>

int main(){
    char buf[69];
    for (int i=0;i<100000000; ++i);

    int ret = read(STDIN_FILENO, buf, sizeof(buf));
}
