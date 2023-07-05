#include <iostream>

template <typename T = void>
constexpr std::string f(const std::string &separator,
			const std::string &conjunctor, const std::string &left,
			const std::string &right)
{
	std::cout << "I'm in base case\n";
	return left + " " + separator + " '" + right + "' ";
}

template <typename... Args>
constexpr std::string f(const std::string &separator,
			const std::string &conjunctor, const std::string &left,
			const std::string &right, const Args &...args)
{
	// std::cout << a << " is matched with " << b << ", ";
	return left + " " + separator + " '" + right + "' " + conjunctor + " "
	       + f(separator, conjunctor, args...);
}

template <typename... Args>
constexpr void isTableEmpty(const std::string &tableName)
{
	// static_assert(sizeof...(args) % 2 == 0, "");
	std::cout << "select * from " << tableName << "\n";
}

template <typename... Args>
constexpr void isTableEmpty(const std::string &tableName, const Args &...args)
{
	// static_assert(sizeof...(args) % 2 == 0, "");
	std::cout << "select * from " << tableName << " where "
		  << f("=", "and", args...) << "\n";
}

// template <typename... Args>
// constexpr bool isTableEmpty(const std::string &tableName, const std::string
// &a, 			    const std::string &b, const Args &...args)
//{
//	// static_assert(sizeof...(args) % 2 == 0, "");
//	std::cout << " table name is " << tableName << "\n ";
//	f(a, b, args...);
//	return false;
// }


int main()
{
	// isTableEmpty("myTableName", "1", "2", "3", "4");
	// isTableEmpty("IPDU", "ACCESS", "GG", "INPORTEND", "45128");
	// isTableEmpty("IPDU", "ACCESS", "GG");

	// this is fine with non-constexpr ...
	std::cout << f<void>("=", "and", "ACCESS", "GG") << "\n";
}
