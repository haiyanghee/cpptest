#include <string.h>
#include <stdio.h>

char shorterStr[] = "someStrHere";
char longerStr[] = "someStrHereAndBeyonddd";

char testStr[4] = "123";

int main(){
    char buf[sizeof(shorterStr)+2] = {0};
    //char buf[sizeof(shorterStr)+69] = {0};

    for (int i=0;i<sizeof(buf)-1;++i) //no overwrite the null terminating byte
        buf[i] = 'a';

    printf("originally buf = %s\n", buf);
    //strncpy(buf, shorterStr, sizeof(shorterStr)-1);
    //strncpy(buf, str, sizeof(str)); //TODO: NOT SAFE!

    //strncpy(buf, shorterStr, sizeof(buf)-1);
    //strncpy(buf, shorterStr, sizeof(buf)); //TODO: not safe!

    strncpy(buf, longerStr, sizeof(buf)-1);
    //strncpy(buf, longerStr, sizeof(buf)); //TODO: not safe!

    printf("new buf = %s\n", buf);


    char b[2]={69,69}; //length of this string is 1...
    strncpy(b, testStr, 1);
    printf("b[0] = %c, b[1] = %c\n", b[0], b[1]);

    /*
    char buf[4]={69,69,69,0};
    strncpy(buf, "12", 2);
    printf("buf = %s\n", buf);
    */
}
