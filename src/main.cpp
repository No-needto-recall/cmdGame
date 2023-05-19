#include <iostream>
#include "GameMap.h"
#include "ScreenDrawer.h"

using namespace std;

void func() {
	for (char ch = 0; ch < 127; ++ch) {
		cout << ch << " ";
	}
	system("pause");
}

int main(int argc,char* argv[]) {
	func();
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