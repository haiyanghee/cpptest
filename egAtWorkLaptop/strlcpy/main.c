#include <stdio.h>
#include <string.h>

//gcc $(pkg-config --cflags libbsd-overlay) main.c $(pkg-config --libs libbsd-overlay)
int main(){
    char buf[4];
    strlcpy(buf, "12345", 3);
    printf("buf = %s\n", buf);
    strlcpy(buf, "1", sizeof(buf));
    printf("buf = %s\n", buf);
}
