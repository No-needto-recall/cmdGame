#include <iostream>
#include "GameMap.h"
#include "ScreenDrawer.h"

using namespace std;


int main(int argc,char* argv[]) {

#if 1

	auto map = GameMapFactory::getInstance().createFromConf();
	while(1){
		map->Print();
		ScreenDrawer::getInstance().swapBuffers();
		Sleep(1000);
	}

#endif // 0
	return 0;


}