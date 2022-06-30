#pragma once

#include "colossus/core/defs.h"

typedef enum {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} LogLevel;

extern void _logMessage(LogLevel level, const char *file, U32 line, const char *message, ...);

#define logFatal(message, ...) _logMessage(LOG_LEVEL_FATAL, __FILE__, __LINE__, message, ##__VA_ARGS__)
#define logError(message, ...) _logMessage(LOG_LEVEL_ERROR, __FILE__, __LINE__, message, ##__VA_ARGS__)
#define logWarn(message, ...)  _logMessage(LOG_LEVEL_WARN, __FILE__, __LINE__,  message, ##__VA_ARGS__)
#define logInfo(message, ...)  _logMessage(LOG_LEVEL_INFO, __FILE__, __LINE__, message, ##__VA_ARGS__)

#ifdef COLOSSUS_RELEASE
    #define logDebug(message, ...)
#else
    #define logDebug(message, ...) _logMessage(LOG_LEVEL_DEBUG, __FILE__, __LINE__, message, ##__VA_ARGS__)
#endif
