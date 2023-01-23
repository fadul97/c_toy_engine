#ifndef LF_LOGGER_H
#define LF_LOGGER_H

#include "defines.h"
#include "error_list.h"

#define LOG_FATAL_ENABLED 1
#define LOG_ERROR_ENABLED 1

// #define LF_RELEASE 1

#if LF_RELEASE == 1
#define LOG_WARN_ENABLED 0
#define LOG_DEBUG_ENABLED 0
#define LOG_INFO_ENABLED 0
#else
#define LOG_WARN_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_INFO_ENABLED 1
#endif

typedef enum LogLevel
{
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_DEBUG = 3,
    LOG_LEVEL_INFO = 4,
} LogLevel;

void log_output(LogLevel level, enum Error err, const char* message, ...);

#ifndef LF_FATAL
#define LF_FATAL(error, message, ...) log_output(LOG_LEVEL_FATAL, error, message, ##__VA_ARGS__);
#endif

#ifndef LF_ERROR
#define LF_ERROR(error, message, ...) log_output(LOG_LEVEL_ERROR, error, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define LF_WARN(message, ...) log_output(LOG_LEVEL_WARN, 0, message, ##__VA_ARGS__);
#else
#define LF_WARN(message, ...);
#endif

#if LOG_DEBUG_ENABLED == 1
#define LF_DEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, 0, message, ##__VA_ARGS__);
#else
#define LF_DEBUG(message, ...);
#endif

#if LOG_INFO_ENABLED == 1
#define LF_INFO(message, ...) log_output(LOG_LEVEL_INFO, 0, message, ##__VA_ARGS__);
#else
#define LF_INFO(message, ...);
#endif

#endif // LF_LOGGER_H
