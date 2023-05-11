#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

class Log {
public:
    // 获取Log类的唯一实例
    static Log& getInstance();

    // 删除拷贝构造函数和赋值操作
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

    // 将信息写入文件
    void writeToFile(const string& message);

    // 记录错误信息，包括函数位置和名称
    void logError(const string& message, const string& functionName, const string& filePath, int lineNumber);

    // 记录日常信息，包括函数位置和名称
    void logInfo(const string& message, const string& functionName, const string& filePath, int lineNumber);
private:
    // 私有构造函数
    Log();

    // 析构函数
    ~Log();

    // 打开日志监控窗口
    void openMonitoringWindow();

    // 关闭日志监控窗口
    void closeMonitoringWindow();

    // 计算日志文件中的行数
    size_t countLines();

    ofstream logFile_;
    size_t currentLine_; // 当前行
    const size_t maxLines_ = 5000; // 最大行数
    //进程信息
    PROCESS_INFORMATION _pi;
    STARTUPINFOW _si;
};

// 定义宏，用于简化错误日志记录
#define LOG_ERROR(message) Log::getInstance().logError(message, __FUNCTION__, __FILE__, __LINE__)
#define LOG_INFO(message) Log::getInstance().logInfo(message, __FUNCTION__, __FILE__, __LINE__)

