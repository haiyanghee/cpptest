all:
	#NOTE: if put sameTranslationUnit.cpp before main.cpp, it gives the "correct" answer (but by chance, as its technically undefined)
	#g++ -std=c++11 sameTranslationUnit.cpp main.cpp
	#if we put main before sameTranslationUnit, then we can reproduce the "unspecified" initialization order
	g++ -std=c++11 main.cpp sameTranslationUnit.cpp
