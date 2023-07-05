// clang-format off
#include <bits/stdc++.h>

using namespace std;

void f(int) { cout << "1"; }   // 1
void f(int &) { cout << "2"; } // 2
 void f(int &&) { cout << "3"; } // 3


int main()
{
	int x;
	//f(x);
	//f(x + 1);
	 f(3);
}
