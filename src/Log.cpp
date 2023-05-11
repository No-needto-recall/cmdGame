#include "Log.h"

Log& Log::getInstance() {
    static Log instance;
    return instance;
}

void Log::writeToFile(const string& message) {
    if (logFile_.is_open()) {
        if (currentLine_ >= maxLines_) {
            // 从文件开头重新覆写
            logFile_.seekp(0);
            currentLine_ = 0;
        }
        logFile_ << message << endl;
        logFile_.flush();
        currentLine_++;
    }
    else {
        cerr << "Unable to write to log file." << endl;
    }
}

void Log::logError(const string& message, const string& functionName, const string& filePath, int lineNumber) {
    string errorMessage = "Error: " + message + " in function " + functionName + " at " + filePath + ":" + std::to_string(lineNumber);
    writeToFile(errorMessage);
}

void Log::logInfo(const string& message, const string& functionName, const string& filePath, int lineNumber) {
    string infoMessage = "Info: " + message + " in function " + functionName + " at " + filePath + ":" + std::to_string(lineNumber);
    writeToFile(infoMessage);
}

Log::Log() {
    logFile_.open("../log/log.txt", std::ios_base::out | std::ios_base::app);
    currentLine_ = countLines();
    openMonitoringWindow();
}

Log::~Log() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
    closeMonitoringWindow();
}

void Log::openMonitoringWindow() {
    // 创建一个新的进程并启动PowerShell窗口
    ZeroMemory(&_si, sizeof(_si));
    _si.cb = sizeof(_si);
    ZeroMemory(&_pi, sizeof(_pi));

    wstring command = L"powershell.exe -NoExit -Command \"Get-Content ..\\log\\log.txt -Wait\"";

    if (!CreateProcessW(NULL, &command[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &_si, &_pi)) {
        cerr << "CreateProcess failed: " << GetLastError() << endl;
    }
}

void Log::closeMonitoringWindow() {
    if (_pi.hProcess) {
        // 终止powershell进程
        TerminateProcess(_pi.hProcess, 0);
        CloseHandle(_pi.hProcess);
        CloseHandle(_pi.hThread);
    }
}

size_t Log::countLines() {
    ifstream inFile("../log/log.txt");
    string line;
    size_t count = 0;

    while (getline(inFile, line)) {
        ++count;
    }

    inFile.close();
    return count;
}
