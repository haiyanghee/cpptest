#include <stdio.h>
#include <string.h>

char str[] = "12345";
char buf[3];
int main(){
    //strncpy(buf, str, sizeof(buf)-1);
    strncpy(buf, str, sizeof(buf));
    for (int i=0;i<sizeof(buf);++i){
        printf("buf[%d] = %c\n", i, buf[i]);
    }
}
