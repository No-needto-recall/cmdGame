#include <random>
#include "GameTool.h"

int GameTool::randomAtoB(const int& a, const int& b)
{
	::srand(std::random_device()());
	return a+::rand()%(b-a+1);
}
