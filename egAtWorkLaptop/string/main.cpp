#include <string>
#include <iostream>

int main()
{
	/*
	std::string s{"hii 1; 2; ah"};
	// std::string s{"select * from NETWORK;"};
	std::string b{"hii 1 2 hahahah"};
	auto pos = s.find_last_of(';');
	std::cout << "substr = " << s.substr(0, pos + 1) << "\n";
	std::cout << "erase = " << s.erase(pos) << "\n"; // will erase to the
	// end

	std::cout
	    << "erase = " << s.erase(pos)
	    << "\n"; // will erase to the std::cout << "s = " << s << "\n";
	std::cout << "find pos? = " << (pos != std::string::npos)
		  << "\n"; // will erase to the
	pos = b.find_last_of(';');
	std::cout << "find pos? = " << (pos != std::string::npos)
		  << "\n"; // will erase to the=
			   */

	// std::string lSql{"select count(*) as COUNT from (select * from
	// DFNI;"};


	///*
	// std::string lSql{"select  1;asdf"};
	//  std::string lSql{"select * from NETWORK;"};
	std::string lSql{";"};

	const auto pos = lSql.find_last_of(';');
	if (pos != std::string::npos) {
		std::cout << "pos = " << pos << "\n";
		std::cout << "substr = '" << lSql.substr(0, pos) << "'\n";
		lSql.erase(pos); // this will erase from the last position of
				 // ';' until the en
	}
	std::cout << lSql << "\n";
	//*/
}
