#include "Utils/LogManager.h"
#include "Utils/utility.h"
#include <cassert>
#include <cstdarg>

LogManager::LogManager()
    : m_do_flush{ false }
    , m_log_to_screen{ false }
    , m_log_time_string{ false }
    , m_p_file{ nullptr }
    , m_log_level{ DEFAULT_LOG_LEVEL }
{
    setType("LogManager");
}

LogManager::~LogManager()
{
    shutDown();
}

/// @brief Get the one and only instance of the LogManager.
/// @return The LogManager instance.
LogManager& LogManager::getInstance()
{
    static LogManager logManager;
    return logManager;
}

/// @brief Start up the LogManager (open logfile "model-viewer.log").
/// @return 
int LogManager::startUp()
{
    m_p_file = fopen(LOGFILE_NAME.c_str(), "w");

    if (m_p_file)
    {
        Manager::startUp();
    }

    return m_p_file ? 0 : -1;
}

// Shut down the LogManager (close logfile).
void LogManager::shutDown()
{
    if (m_p_file)
    {
        int res = fclose(m_p_file);
        assert(res == 0);
        m_p_file = nullptr;
        Manager::shutDown();
    }
}

void LogManager::setLogLevel(int log_level)
{
    m_log_level = log_level;
}

void LogManager::setLogToScreen(bool do_log_to_screen)
{
    m_log_to_screen = do_log_to_screen;
}

void LogManager::setFlush(bool do_flush)
{
    m_do_flush = do_flush;
}

void LogManager::setLogTime(bool do_log_time)
{
    m_log_time_string = do_log_time;
}


int LogManager::writeLogImp(int log_level, const char* fmt, va_list args) const
{
    int res = 0;
    const char* log_level_str_p = nullptr;

    if (!isStarted())
    {
        return -1;
    }

    if (log_level < m_log_level)
    {
        return 0;
    }

    assert(m_p_file);

    if (m_log_time_string)
    {
        if (m_log_to_screen)
        {
            printf("%s: ", getTimeString());
        }

        res += fprintf(m_p_file, "%s: ", getTimeString());
        if (res < 0)
        {
            return res;
        }
    }

    switch (log_level)
    {
    case DEBUG_LEVEL:
        log_level_str_p = "DEBUG: ";
        break;
    case INFO_LEVEL:
        log_level_str_p = "INFO: ";
        break;
    case IMPORTANT_LEVEL:
        log_level_str_p = "IMPORTANT: ";
        break;
    case INT_MAX:
        log_level_str_p = "";
        break;
    default:
        static char lvl_str[24];
        int snprintf_res = snprintf(lvl_str, sizeof(lvl_str), "%d: ",
            log_level);
        assert(snprintf_res > 0);
        log_level_str_p = lvl_str;
    }

    assert(log_level_str_p);

    if (m_log_to_screen)
    {
        printf("%s", log_level_str_p);
        vprintf(fmt, args);
    }

    res += fprintf(m_p_file, "%s", log_level_str_p);
    if (res < 0)
    {
        return res;
    }

    res += vfprintf(m_p_file, fmt, args);
    if (res < 0)
    {
        return true;
    }

    if (m_do_flush)
    {
        int flush_res = fflush(m_p_file);
        assert(flush_res == 0);
    }

    return res;
}

int LogManager::writeLog(int log_level, const char* fmt, ...) const
{
    int res = 0;

    va_list args;
    va_start(args, fmt);
    res = writeLogImp(log_level, fmt, args);
    va_end(args);

    return res;
}

int LogManager::writeLog(const char* fmt, ...) const
{
    int res = 0;

    va_list args;
    va_start(args, fmt);
    res = writeLogImp(INT_MAX, fmt, args);
    va_end(args);

    return res;
}
