#include <stdio.h>
#include <stddef.h>

#define FNV_offset_basis 0xcbf29ce484222325
#define FNV_prime 0x100000001b3

size_t FNVHash(const char* str){
    size_t hash = FNV_offset_basis;
    while( *str != '\0'){
        hash = hash * FNV_prime;
        hash = hash ^ *str;
        ++str;
    }
    return hash;
}

int main(){
    printf("%zu\n", FNVHash("abc"));
    printf("%zu\n", FNVHash("bbc"));
    printf("%zu\n", FNVHash("abd"));
}
