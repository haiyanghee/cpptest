#define X(n) X##n

#define Xint* 3

char* extractString(char* asdf);

int main(){
    X(int*);

}
