#include "Mytool.h"

int Mytool::randomNum(int a, int b)
{
	::srand(std::random_device()());
	return a + ::rand() % (b - a + 1);
}
