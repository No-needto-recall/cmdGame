#pragma once

#include <deque>
#include <string>
#include <vector>
#include "ScreenDrawer.h"

class ScreenWindow {
public:
    // 构造函数，接收窗口左上角坐标以及窗口的宽度和高度
    ScreenWindow(int x, int y, int width, int height);

    // 将一段文本添加到窗口的缓冲区中
    void addText(const std::string& str);

    // 显示下一页的文本
    void displayNextPage();

private:
    // 刷新窗口，将当前缓冲区中的文本显示出来
    void refresh();
    void splitText(const std::string& text);

    COORD topLeft;  // 窗口左上角的坐标
    int width, height;  // 窗口的宽度和高度
    std::deque<std::string> lines;  // 当前需要显示的文本行
    std::deque<std::string> allLines;  // 所有待显示的文本行
};