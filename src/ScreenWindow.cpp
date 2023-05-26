#include "ScreenWindow.h"
#include <sstream>

ScreenWindow::ScreenWindow(int x, int y, int width, int height)
	: topLeft{ static_cast<SHORT>(x), static_cast<SHORT>(y) }, width(width), height(height) {}

void ScreenWindow::addText(const std::string& str) {
    std::istringstream stream(str);
    std::string line;
    while (std::getline(stream, line,'\n')) {
        allLines.push_back(line);
    }
}

void ScreenWindow::displayNextPage() {
    if (allLines.empty()) {
        refresh();
        return;
    }

    lines.clear();
    int i = 0;
    while (i < height && !allLines.empty()) {
        std::string line = allLines.front();
        allLines.pop_front();

        while (line.length() > width) {
            lines.push_back(line.substr(0, width));
            line = line.substr(width);
            ++i;
            // 到达页面最大行数，将未显示完全的行推回 allLines
            if (i >= height) {
                allLines.push_front(line);
                refresh();
                return;
            }
        }

        // 如果当前行在宽度允许的范围内，直接添加到 lines
        if (i < height) {
            lines.push_back(line);
            ++i;
        }
    }
    refresh();
}


void ScreenWindow::refresh() {
    ScreenDrawer& drawer = ScreenDrawer::getInstance(); // 获取ScreenDrawer的单例实例
    int y = topLeft.Y;
    if (allLines.empty()&& lines.empty()) {
        for (int i = 0; i < height; ++i) {
            drawer.drawString(topLeft.X, y + i, std::string(width, ' '));
        }
    }
    else {
		for (int i = 0; i < height; ++i) {
            drawer.drawString(topLeft.X, y + i, std::string(width, ' '));
        }
        for (const auto& line : lines) {
            drawer.drawString(topLeft.X, y++, line);
        }
    }
    lines.clear();
}

