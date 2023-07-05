#include <stdio.h>
#include <stddef.h>

struct A {
	// char a1;
	char a3;
	short a5;
	int a4;	 // 2 bytes
	long a2; // 4 bytes
};

int main()
{
	printf("%lu\n", sizeof(struct A));

	// printf("%lu\n", offsetof(struct A, a1));
	printf("%lu\n", offsetof(struct A, a2));
	printf("%lu\n", offsetof(struct A, a3));
	printf("%lu\n", offsetof(struct A, a5));
	printf("%lu\n", offsetof(struct A, a4));
}
