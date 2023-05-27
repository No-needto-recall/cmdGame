#include <sstream>
#include "ScreenWindow.h"
#include "GameTool.h"
// 计算一个字符的显示宽度
int displayWidth(const std::string& ch) {
    return (unsigned char)ch[0] < 128 ? 1 : 2;
}
// 切割字符串为一个个字符
std::vector<std::string> splitCharacters(const std::string& text) {
    std::vector<std::string> chars;
    for (size_t i = 0; i < text.length(); ) {
        size_t charLen = (unsigned char)text[i] < 128 ? 1 : 3;
        chars.push_back(text.substr(i, charLen));
        i += charLen;
    }
    return chars;
}
ScreenWindow::ScreenWindow(int x, int y, int width, int height)
	: topLeft{ static_cast<SHORT>(x), static_cast<SHORT>(y) }, width(width), height(height) {}

void ScreenWindow::addText(const std::string& str) {
    splitText(str);
}

void ScreenWindow::splitText(const std::string& text) {
    std::stringstream ss(text);
    std::string line;
    while (std::getline(ss, line)) {
        std::vector<std::string> chars = splitCharacters(line);
        std::string currentLine;
        int currentWidth = 0;
        for (const std::string& ch : chars) {
            int chWidth = displayWidth(ch);
            if (currentWidth + chWidth > width) {
                allLines.push_back(currentLine);
                currentLine.clear();
                currentWidth = 0;
            }
            currentLine += ch;
            currentWidth += chWidth;
        }
        if (!currentLine.empty()) {
            allLines.push_back(currentLine);
        }
    }
}
void ScreenWindow::displayNextPage() {
    if (allLines.empty()) {
        refresh();
        return;
    }

    lines.clear();
    int i = 0;
    for (int i = 0; i < height && !allLines.empty(); ++i) {
        lines.push_back(allLines.front());
        allLines.pop_front();
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
            drawer.drawWideString(topLeft.X, y++, GameTool::stringToWstring(line));
        }
    }
    lines.clear();
}

