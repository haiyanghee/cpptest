#include <stdio.h>
#include <getopt.h>

int main(int argc, char** argv){
    int opt;
    while((opt=getopt(argc, argv, "ab:")) != -1){
        switch (opt){
            case 'a':
                printf("found option a!\n");
                break;
            case 'b':
                printf("found option b!\n");
                break;
            default: 
                printf("unrecognized option...\n");
        }
    }

    //print trailing files
    for (int i=optind; i < argc; ++i){
        printf("extra arg '%s'\n", argv[i]);
    }
}
