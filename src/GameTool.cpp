#include <random>
#include <locale>
#include <codecvt>
#include "GameTool.h"

int GameTool::randomAtoB(const int& a, const int& b)
{
	::srand(std::random_device()());
	return a+::rand()%(b-a+1);
}



std::wstring GameTool::stringToWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(str);
    return wstr;
}

