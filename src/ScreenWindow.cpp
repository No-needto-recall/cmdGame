#include "ScreenWindow.h"
#include <sstream>

ScreenWindow::ScreenWindow(int x, int y, int width, int height)
	: topLeft{ static_cast<SHORT>(x), static_cast<SHORT>(y) }, width(width), height(height) {}

void ScreenWindow::addText(const std::string& str) {
    std::istringstream stream(str);
    std::string line;
    while (std::getline(stream, line)) {
        allLines.push_back(line);
    }
}

void ScreenWindow::displayNextPage() {
    if (allLines.empty()) {
        return;
    }

    lines.clear();
    int i = 0;
    while (i < height && !allLines.empty()) {
        std::string line = allLines.front();
        allLines.pop_front();

        while (line.length() > width) {
            if (i >= height) {
                allLines.push_front(line);  // 将未处理完的部分推回 allLines
                return;
            }
            lines.push_back(line.substr(0, width));
            line = line.substr(width);
            ++i;
        }
        if (i < height) {
            lines.push_back(line);
            ++i;
        }
        else {
            allLines.push_front(line);  // 如果高度已满，将剩余部分推回 allLines
        }
    }
    refresh();
}

void ScreenWindow::refresh() {
    ScreenDrawer& drawer = ScreenDrawer::getInstance(); // 获取ScreenDrawer的单例实例
    int y = topLeft.Y;
    for (const auto& line : lines) {
        drawer.drawString(topLeft.X, y++, line);
    }
}
