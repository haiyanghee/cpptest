#include <iostream>
#include <sys/epoll.h>

void f(int &i)
{
	std::cout << "in f, initially i = " << i << "\n";
	i = -1;
	std::cout << "in f, after changing, i = " << i << "\n";
}

int main()
{
	/*
	    union U {
	     void *ptr;
	     int fd;
	     float f;
	    };

	    union U myU;
	    myU.fd = 2;
	    std::cout << "before f, after changing, i = " << myU.fd << "\n";
	    f(myU.fd);
	    std::cout << "outside f, after changing, i = " << myU.fd << "\n";
	*/


	/*
	    struct epoll_event ee = {0};
	    ee.data.fd = 2;
	    const int &wdf = ee.data.fd;

	    ee.data.fd = 69;
	    std::cout << "wdf = " << wdf << ", ee.data.fd = " << ee.data.fd <<
	   "\n";


	    int a = 2;
	    const int &gg = a;
	    a = 420;
	    std::cout << "gg = " << gg << ", a = " << a << "\n";
	*/

	struct epoll_event ee = {0};
	ee.data.fd = 2;
	int temp = ee.data.fd;
	std::cout << "before f, temp = " << temp
		  << ", ee.data.fd = " << ee.data.fd << "\n";
	f(temp);
	std::cout << "outside f, after changing, temp = " << temp << "\n";
	ee.data.fd = temp;
	std::cout << "outside f, temp = " << temp
		  << ", ee.data.fd = " << ee.data.fd << "\n";
}
