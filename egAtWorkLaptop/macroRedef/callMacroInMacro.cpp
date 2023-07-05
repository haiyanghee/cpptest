//#include <stdio.h>

#define A(a,b) some line \ 
printf("a = %d, b = %s\n", a, b);

#define B(a,b) some B line \
    A(1 , b)

#define C(a,b) B( a , b )

//#define D(a,b) A(1,b)

int main(){
    char s_a[] = "hiii";
    //B(3,s_a);
    C(3,s_a);
}
