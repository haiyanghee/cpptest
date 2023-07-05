#include <iostream>

template <size_t N>
class string_literal
{
	const char (&_lit)[N + 1];

    public:
	// constructor
	constexpr string_literal(const char (&lit)[N + 1])
	{
		static_assert(lit[N] == '\0',
			      "last bit isn't null terminated!");
		_lit(lit);
	}
	// index operator
	constexpr char operator[](size_t i) const
	{
		static_assert(i >= 0 && i < N,
			      "Index to string_literal is out of bounds!");
		return _lit[i];
	}
};

template <size_t N_PLUS_1>
constexpr auto literal(const char (&lit)[N_PLUS_1])
    -> string_literal<N_PLUS_1 - 1>
{
	return string_literal<N_PLUS_1 - 1>(lit);
}
