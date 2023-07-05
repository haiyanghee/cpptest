#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>

void printMemLayout(const char* data, size_t byteSize){
    for (size_t i=0;i<byteSize-1;++i)
        printf("%x|", data[i]);
    if (byteSize>0)
        printf("%x", data[byteSize-1]);
    printf("\n");
}

int main(){
    uint32_t a = 0x10203040;
    char* aPtr = (char*)&a;
    printMemLayout(aPtr, sizeof(a));

    uint32_t bitmask = 0x0000FFFF;
    printMemLayout((const char*)&bitmask, sizeof(bitmask));

    printMemLayout((const char*)(uint16_t*)&a, sizeof(uint16_t));

    char buf[] = {0x10, 0x20, 0x30, 0x40};
    printMemLayout(buf, sizeof(buf));

    uint16_t highPartOfInput;
    memcpy(&highPartOfInput, buf, sizeof(uint16_t));
    uint16_t highPart = ntohs(highPartOfInput);
    printMemLayout((char*)&highPart, sizeof(highPart));

    uint16_t lowPartOfInput;
    memcpy(&lowPartOfInput, buf+2, sizeof(uint16_t));
    printf("lower part of input:\n");
    printMemLayout((char*)&lowPartOfInput, sizeof(lowPartOfInput));
    uint16_t lowPart = ntohs(lowPartOfInput);
    printMemLayout((char*)&lowPart, sizeof(lowPart));

    uint32_t shiftedHighPart= highPart << 16;
    printMemLayout((char*)&shiftedHighPart, sizeof(shiftedHighPart));
    uint32_t end = shiftedHighPart + lowPart;
    printMemLayout((char*)&end, sizeof(end));

   
    uint32_t actual;
    memcpy(&actual, buf, sizeof(buf));
    uint32_t actualEnd = ntohl(actual);
    printMemLayout((char*)&actualEnd, sizeof(actualEnd));

}
