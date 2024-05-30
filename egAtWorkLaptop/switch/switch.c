#include <stdio.h>

//clang -Xclang -ast-dump switch.c  | less -R
int main(){
    switch (3){
        //default:
        //    printf("in default\n");
        case 1: {
                    printf("normal way\n");
                    break;
                }
        case 2: 
            printf("what \n");
            int i = 1;
            printf("what1 \n");
            printf("i = %d\n", i);
            //printf("should be oustide case 2 label?\n");
        default:
            i=2;
            printf("in default, i=%d\n",i);
    }
}
