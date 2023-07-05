#include <string>
#include "stdio.h"

class A
{
    public:
	int a;
};
class B
{
    public:
	int b;
};

class C
{
    public:
	A myA;
	B myB;
};

enum ENUM { E_A, E_B, E_C };

struct MyS {
	///*
	void operator()(const A &a, C &c)
	{
		c.myA = a;
		printf("in A overload\n");
	}
	void operator()(const B &b, C &c)
	{
		c.myB = b;
		printf("in B overload\n");
	}
	//*/
	// void operator()(const A &a, A &aa) { aa = a; }
	// void operator()(const B &a, B &aa) { aa = a; }
};

// template <typename T, enum ENUM e>
template <typename T, typename S>
constexpr void f(C &c, enum ENUM e)
{
	T obj;
	S s;
	s(obj, c);

	// std::string asdf;
	/*
	    if (e == E_A) {
		    s(obj, c.myA);
	    } else if (e == E_B) {
		    s(obj, c.myB);
	    }
	*/
}

int main()
{
	C c;
	f<A, MyS>(c, E_A);
	f<B, MyS>(c, E_B);
}
