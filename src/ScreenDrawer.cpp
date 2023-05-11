#include "ScreenDrawer.h"


ScreenDrawer::ScreenDrawer(int width,int height)
	: _screenWidth(width)
	, _screenHeight(height)
{
	_buffer1 = createConsoleBuffer();
	_buffer2 = createConsoleBuffer();
	_activeBuffer = _buffer1;
	_drawingBuffer = _buffer2;
}


//设置文本颜色
void ScreenDrawer::setTextColor(WORD color) {
	SetConsoleTextAttribute(_activeBuffer, color);
}


//在指定坐标绘制一个字符
void ScreenDrawer::drawCharacter(short x, short y,const char ch){
	if (x < 0 || x >= _screenWidth ||
		y < 0 || y >= _screenHeight) {
		LOG_ERROR("错误的绘制坐标");
		return;
	}
	DWORD charsWritten;
	COORD coord = { x,y };
	WriteConsoleOutputCharacterA(_drawingBuffer, &ch, 1, coord
		, &charsWritten);
}

//清除、绘制、切换
void ScreenDrawer::clear_drawChar_swap(short x, short y, const char ch) {
	clearScreen();
	drawCharacter(x, y, ch);
	swapBuffers();
	Sleep(500);
}

//在指定坐标绘制一个字符串
//对换行进行了处理
void ScreenDrawer::drawString(short x,short y, const string &&str) {
	COORD coord = { x,y };

	for (const  char ch : str) {
		if (ch == '\n') {
			coord.X = x;
			++coord.Y;
		}
		else {
			drawCharacter(coord.X, coord.Y, ch);
			++coord.X;
		}
	}
}

//绘制一个圆
void ScreenDrawer::drawCircle(int centerX, int centerY, int radius) {
	for (int y = centerY - radius; y <= centerY + radius; ++y) {
		for (int x = centerX - radius; x <= centerX + radius; ++x) {
			// 计算当前点到圆心的距离
			double distance = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));

			// 判断当前点是否在圆的边界附近
			if (std::abs(distance - radius) < 0.5) {
				drawCharacter(x, y, '*');
			}
		}
	}
}

//清空屏幕
void ScreenDrawer::clearScreen() {
    COORD topLeft = {0, 0};
    DWORD bufferSize = _screenWidth* _screenHeight;
    DWORD charsWritten;

    // 使用空格字符填充缓冲区
    FillConsoleOutputCharacterA(_drawingBuffer, ' ', bufferSize, topLeft, &charsWritten);

    // 使用默认的文本属性填充缓冲区
    FillConsoleOutputAttribute(_drawingBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, bufferSize, topLeft, &charsWritten);
}


//清除缓冲区
void ScreenDrawer::clearBuffer(HANDLE& buffer) {
	COORD topLeft = {0, 0};
    DWORD bufferSize = _screenWidth* _screenHeight;
    DWORD charsWritten;

    // 使用空格字符填充缓冲区
    FillConsoleOutputCharacterA(buffer, ' ', bufferSize, topLeft, &charsWritten);

    // 使用默认的文本属性填充缓冲区
    FillConsoleOutputAttribute(buffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, bufferSize, topLeft, &charsWritten);
}


//创建缓冲区
HANDLE ScreenDrawer::createConsoleBuffer() {
	// 创建一个新的控制台屏幕缓冲区
	HANDLE hNewBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, // 允许读写操作
		FILE_SHARE_READ | FILE_SHARE_WRITE, // 允许其他进程共享读写
		NULL, // 安全属性（NULL表示使用默认设置）
		CONSOLE_TEXTMODE_BUFFER, // 指定为文本模式缓冲区
		NULL // 不使用额外的数据
	);

	// 将新创建的缓冲区设置为活动缓冲区
	SetConsoleActiveScreenBuffer(hNewBuffer);

	// 返回新创建的缓冲区句柄
	return hNewBuffer;
}


//切换缓冲区
void ScreenDrawer::swapBuffers() {
	std::swap(_activeBuffer, _drawingBuffer);
	SetConsoleActiveScreenBuffer(_activeBuffer);
}
