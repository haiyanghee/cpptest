#include <iostream>

using namespace std;

struct A {
	int a;
	// A() { cout << "in A() \n"; }
	A(int aa) : a(aa) { cout << "in A(int aa) \n"; }
};

struct B : A {
	int b;
	B() { cout << "in B() \n"; }
	B(int bb) : b(bb) { cout << "in B(int bb) \n"; }
};

int main()
{
	B b1{};
	B b2{2};
}
