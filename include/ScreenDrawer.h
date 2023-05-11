#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include "Log.h"

using std::cout;
using std::endl;
using std::string;

//对于windows的窗口，左上角为坐标起点。
//x轴从左到右递增
//y轴从上到下递增


class ScreenDrawer {

public:
	//单例
	static ScreenDrawer& getInstance() {
		static ScreenDrawer instance;
		return instance;
	}
	
	//设置文本颜色
	void setTextColor(WORD color);

	//在指定坐标绘制一个字符
	void drawCharacter(short x, short y,const char ch);
	//清除draw，绘制，切换
	void clear_drawChar_swap(short x, short y, const char ch);
	//在指定坐标绘制一个字符串
	void drawString(short x, short y, const string &&str);

	//绘制一个圆
	void drawCircle(int centerX, int centerY, int radius);

	//清除drawingBuffer
	void clearScreen();

	//清除指定缓冲区
	void clearBuffer(HANDLE&);

	//切换缓冲区
	void swapBuffers();

	ScreenDrawer(const ScreenDrawer&) = delete;
	ScreenDrawer& operator = (const ScreenDrawer&) = delete;
private:
	//创建缓冲区
	HANDLE createConsoleBuffer();
	//构造函数私有
	ScreenDrawer(int width = 30, int height = 30);
	~ScreenDrawer(){}

private:
	HANDLE _buffer1, _buffer2;//缓冲区
	HANDLE _activeBuffer;//活跃缓冲区
	HANDLE _drawingBuffer;//绘制缓冲区
	int _screenWidth;//屏幕宽度
	int _screenHeight;//屏幕高度

};


#define DRAWER(X,Y,msg) ScreenDrawer::getInstance().clear_drawChar_swap(X,Y,msg) 


