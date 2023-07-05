#include <bits/stdc++.h>

struct A {
	int a;
};

void f(const A &a) { printf("In const ref overload\n"); }
void f(A &&a) { printf("In rvalue overload\n"); }

void g(const int &a) { printf("In const ref overload\n"); }
void g(int &&a) { printf("In rvalue overload\n"); }

int getInt() { return 3; }

int main()
{
	A a;
	// f(a);


	// Scott mayer trolled... can't simply cast an object to rvalue ref
	// without std::move... A&& aRef = a;
	// auto &&aAutoRef = a;
	// f(aAutoRef);


	// experiment shows that even if you cast a lvalue to a rvalue, since it
	// will have a name, it will be lvalue
	A &&aRef = std::move(a);
	f(aRef);
	auto &&aAutoRefAssign = aRef;
	f(aAutoRefAssign);
	auto &&aAutoRefMove = std::move(a);
	f(aAutoRefMove);

	// even binding a rvalue doesn't work...
	A &&actualARef{1};
	f(actualARef);
	// the only way to invoke the rvalue overload is to call std::move when
	// calling the function
	f(std::move(a));

	// even binding a rvalue doesn't work...
	int &&tempInt = 3;
	g(tempInt);
	int &&tempInt2 = getInt();
	g(tempInt2);
}
