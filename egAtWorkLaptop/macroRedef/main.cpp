#include <stdio.h>
#define WHAT 2;

struct A {
	int mya;
};

#define MACRO(objname, fieldname)                                              \
	objname.fieldname = 4;                                                 \
	printf("I have a field name " #fieldname "= %d\n", objname.fieldname)

int main()
{
	//#ifdef WHAT
	//#error
	//#endif

	//#undef WHAT

	struct A myobj;
	myobj.mya = 2;

	MACRO(myobj, mya);
}
