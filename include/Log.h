#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

class Log {
public:
    // 获取Log类的唯一实例
    static Log& getInstance() {
        static Log instance;
        return instance;
    }

    // 删除拷贝构造函数和赋值操作
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

    // 将信息写入文件
    void writeToFile(const std::string& message) {
        if (logFile_.is_open()) {
            if (currentLine_ >= maxLines_) {
                // 从文件开头重新覆写
                logFile_.seekp(0);
                currentLine_ = 0;
            }
            logFile_ << message << std::endl;
            logFile_.flush();
            currentLine_++;
        }
        else {
            std::cerr << "Unable to write to log file." << std::endl;
        }
    }

    // 记录错误信息，包括函数位置和名称
    void logError(const std::string& message, const std::string& functionName, const std::string& filePath, int lineNumber) {
        std::string errorMessage = "Error: " + message + " in function " + functionName + " at " + filePath + ":" + std::to_string(lineNumber);
        writeToFile(errorMessage);
    }
    
    // 记录日常信息，包括函数位置和名称
    void logInfo(const std::string& message, const std::string& functionName, const std::string& filePath, int lineNumber) {
        std::string errorMessage = "Info: " + message + " in function " + functionName + " at " + filePath + ":" + std::to_string(lineNumber);
        writeToFile(errorMessage);
    }
private:
    // 私有构造函数
    Log() {
        logFile_.open("log.txt", std::ios_base::out | std::ios_base::app);
        currentLine_ = countLines();
        openMonitoringWindow();
    }

    // 析构函数
    ~Log() {
        if (logFile_.is_open()) {
            logFile_.close();
        }
        closeMonitoringWindow();
    }
    void openMonitoringWindow() {
        // 创建一个新的进程并启动PowerShell窗口
        ZeroMemory(&_si, sizeof(_si));
        _si.cb = sizeof(_si);
        ZeroMemory(&_pi, sizeof(_pi));

        std::wstring command = L"powershell.exe -NoExit -Command \"Get-Content log.txt -Wait\"";

        if (!CreateProcessW(NULL, &command[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &_si, &_pi)) {
            std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
        }
    }
    void closeMonitoringWindow() {
        if (_pi.hProcess) {
            //终止powershell进程
            TerminateProcess(_pi.hProcess,0);
            CloseHandle(_pi.hProcess);
            CloseHandle(_pi.hThread);
        }
    }

    // 计算日志文件中的行数
    size_t countLines() {
        std::ifstream inFile("log.txt");
        std::string line;
        size_t count = 0;

        while (std::getline(inFile, line)) {
            ++count;
        }

        inFile.close();
        return count;
    }

    std::ofstream logFile_;
    size_t currentLine_; // 当前行
    const size_t maxLines_ = 5000; // 最大行数
    //进程信息
    PROCESS_INFORMATION _pi;
    STARTUPINFOW _si;
};

// 定义宏，用于简化错误日志记录
#define LOG_ERROR(message) Log::getInstance().logError(message, __FUNCTION__, __FILE__, __LINE__)
#define LOG_INFO(message) Log::getInstance().logInfo(message, __FUNCTION__, __FILE__, __LINE__)
