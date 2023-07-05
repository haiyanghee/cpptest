all:
	g++ -fPIC -g -O2 -std=gnu++11 -c -Wall -Wextra -Werror main.cpp
	g++ -nodefaultlibs -fPIC -shared  -lstdc++ -lc -o libmain.so main.o
	#g++ -nodefaultlibs -fPIC -shared -Wl,--allow-multiple-definition -Wl,--no-undefined -lstdc++ -lc -o libmain.so main.o
	#g++ -nodefaultlibs -fPIC -shared -Wl,--allow-multiple-definition -lstdc++ -lc -o libmain.so main.o
	#g++ run.cpp -o run.out
	g++ ./main2.cpp -L. -lmain 
