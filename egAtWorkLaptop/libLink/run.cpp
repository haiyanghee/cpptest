
 #include <dlfcn.h>
 #include <stdio.h>

int main(){
     void* lib = dlopen("./libmain.so",RTLD_NOW);
     printf("err: %s\n", dlerror());
     //dlclose(lib);
}
