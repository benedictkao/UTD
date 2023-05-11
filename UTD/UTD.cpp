// UTD.cpp : Defines the entry point for the application.
//
#include "UTD.h"

int main()
{
	utd::array<int, 2> a;
	a.set(0, 0);
	a.set(1, 1);
	std::cout << a.get(0) << ", " << a.get(1) << std::endl;
	return 0;
}
