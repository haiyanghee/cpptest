
template <typename T>
void f(const T& a){
    a = nullptr;
}

int main(){
    int* a;
    f(a);
}

