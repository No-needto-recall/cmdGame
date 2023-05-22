#include <chrono>
#include <iomanip>
#include <sstream>
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
    string filename = extractFileName(filePath);
	string time = " " + getCurrentTiem();
    string errorMessage ="Error: " + message + " in " + functionName + " at " + filename+ ":" + std::to_string(lineNumber)+time;
    writeToFile(errorMessage);
}

void Log::logInfo(const string& message, const string& functionName, const string& filePath, int lineNumber) {
    string filename = extractFileName(filePath);
	string time = " "+ getCurrentTiem();
    string infoMessage = "Info: " + message + " in " + functionName + " at " + filename+ ":" + std::to_string(lineNumber)+time;
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

string Log::getCurrentTiem()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm timeinfo = {};
    localtime_s(&timeinfo, &now_time_t);

    std::stringstream ss;
    ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}


string Log::extractFileName(const string& path)
{
    size_t lastSlash = path.rfind('/');
    size_t lastBackslash = path.rfind('\\');
    size_t pos = (lastSlash != std::string::npos && lastSlash > lastBackslash) ? lastSlash : lastBackslash;
    if (pos != std::string::npos)
        return path.substr(pos + 1);
    else
        return path;
}
