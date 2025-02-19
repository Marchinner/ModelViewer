#pragma once

#include "Core/Manager.h"

#define LM LogManager::getInstance()

#define DEFAULT_LOG_LEVEL INFO_LEVEL

const std::string LOGFILE_NAME = "model-viewer.log";
const int DEBUG_LEVEL = 100;
const int INFO_LEVEL = 200;
const int IMPORTANT_LEVEL = 300;

class LogManager : public Manager
{
public:
    static LogManager& getInstance();

    ~LogManager();

    int startUp();

    void shutDown();

    void setLogLevel(int log_level);

    void setLogToScreen(bool do_log_to_screen = true);

    void setFlush(bool do_flush = true);

    void setLogTime(bool do_log_time = true);

    int writeLog(int log_level, const char* fmt, ...) const;

    int writeLog(const char* fmt, ...) const;

private:
    LogManager();
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    int writeLogImp(int log_level, const char* fmt, va_list args) const;

private:
    bool m_do_flush;
    bool m_log_to_screen;
    bool m_log_time_string;
    FILE* m_p_file;
    int m_log_level;
};