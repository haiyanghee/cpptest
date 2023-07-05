#include <iostream>
#include <string>
#include <map>
#include <utility>


// enum KeyOne { A = 1, B, C, D };
// typedef std::pair<KeyOne, std::string> MyKey;

typedef std::pair<int, std::string> MyKey;

int main()
{
	int A = 1, B = 2, C = 3, D = 4;
	// static const std::map<MyKey, std::string> map{
	//     {{A, "hi"}, "key1"},   {{A, "ai"}, "key2"}, {{A, "ac"}, "key22"},
	//     {{B, "bi"}, "key3"},   {{B, "bj"}, "key4"}, {{B, "aa"}, "key5"},
	//     {{C, "asdf"}, "key6"}, {{D, "sdf"}, "key7"}};

	static const std::map<MyKey, std::string> map{//{{A, "hi"}, "key1"},
						      //{{A, "ai"}, "key2"},
						      //{{A, "ac"}, "key22"},
						      {{B, "bi"}, "key3"},
						      {{B, "bj"}, "key4"},
						      {{B, "aa"}, "key5"},
						      {{C, "asdf"}, "key6"},
						      {{D, "sdf"}, "key7"}};

	// empty map
	static const std::map<MyKey, std::string> map2;

	std::cout << "Printing the map in sorted order:\n";
	for (const auto &i : map) {
		std::cout << "key = <" << i.first.first << ", "
			  << i.first.second << ">, val = " << i.second << "\n";
	}

	// std::cout << "Getting lower bound of B (is 1):\n";
	// auto i = map.lower_bound({B, ""});
	// for (; i != map.end(); ++i) {
	//	std::cout << "key = <" << i->first.first << ", "
	//		  << i->first.second << ">, val = " << i->second
	//		  << "\n";
	// }


	std::cout << "Getting lower bound of 0 (is 1):\n";

	// auto i = map2.lower_bound({0, ""});
	// std::cout << "i == map2.end()" << (i == map2.end()) << "\n";

	auto i = map.lower_bound({10, ""});
	std::cout << "i == map.end()" << (i == map.end()) << "\n";
	// for (; i != map.end(); ++i) {
	//	std::cout << "key = <" << i->first.first << ", "
	//		  << i->first.second << ">, val = " << i->second
	//		  << "\n";
	// }
}
