#include <iostream>


template <typename... Args>
constexpr inline size_t getCount(const Args &...args)
{
	return sizeof...(args);
}

template <size_t N, typename... Args>
constexpr void g(const Args &...args)
{
	std::cout << "how many arguments g has is: " << N << "\n";
}

template <size_t N>
constexpr void gg()
{
	std::cout << "how many arguments gg has is: " << N << "\n";
}

template <typename... Args>
constexpr void f(const Args &...args)
{
	std::cout << "how many arguments f has is: " << getCount(args...)
		  << "\n";
	// const size_t N = getCount(args...);
	// g<getCount(args), Args...>(args...);

	gg<getCount(args...)>();
	// gg<sizeof...(args)>();
}


int main() { f(1, 2, 3); }
