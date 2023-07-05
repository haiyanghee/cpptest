#include <iostream>

template <int N>
class FixedString
{
};

template <typename AnyVar>
void f(AnyVar &a)
{
	std::cout << " in f(AnyVar& a), a =" << a << "\n";
}


template <int N>
void f(FixedString<N> &a)
{
	std::cout << " in f(FixedString<N>& a)\n";
}


struct Asdf {
	typedef int asdf;
};

int main()
{
	FixedString<3> str;
	f(str);
}
