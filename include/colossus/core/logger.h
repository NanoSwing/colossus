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

/*
 * Logs a fatal level message.
 *
 * message - Message.
 */
#define logFatal(message, ...) _logMessage(LOG_LEVEL_FATAL, __FILE__, __LINE__, message, ##__VA_ARGS__)
/*
 * Logs an error level message.
 *
 * message - Message.
 */
#define logError(message, ...) _logMessage(LOG_LEVEL_ERROR, __FILE__, __LINE__, message, ##__VA_ARGS__)
/*
 * Logs a warning level message.
 *
 * message - Message.
 */
#define logWarn(message, ...)  _logMessage(LOG_LEVEL_WARN, __FILE__, __LINE__,  message, ##__VA_ARGS__)
/*
 * Logs an info level message.
 *
 * message - Message.
 */
#define logInfo(message, ...)  _logMessage(LOG_LEVEL_INFO, __FILE__, __LINE__, message, ##__VA_ARGS__)

#ifdef COLOSSUS_RELEASE
    /*
     * Logs a debug level message.
     *
     * message - Message.
     */
    #define logDebug(message, ...)
#else
    /*
     * Logs a debug level message.
     *
     * message - Message.
     */
    #define logDebug(message, ...) _logMessage(LOG_LEVEL_DEBUG, __FILE__, __LINE__, message, ##__VA_ARGS__)
#endif
