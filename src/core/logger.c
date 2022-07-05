#include "colossus/core/logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void _logMessage(LogLevel level, const char *file, U32 line, const char *message, ...)
{
    va_list ptr;
    va_start(ptr, message);

    char message_buffer[1024 * 8];
    vsprintf(message_buffer, message, ptr);
    va_end(ptr);

    static const char *level_prefix[5] = {
        "FATAL",
        "ERROR",
        "WARN ",
        "INFO ",
        "DEBUG",
    };
    static const char *level_color[5] = {
        "\033[1;31m",
        "\033[0;31m",
        "\033[0;33m",
        "\033[0;32m",
        "\033[0;36m"
    };

    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    printf(
        "%.2u:%.2u:%.2u %s%s \033[0m%s:%u: \033[0m%s\n",
        tm_struct->tm_hour,
        tm_struct->tm_min,
        tm_struct->tm_sec,
        level_color[level],
        level_prefix[level],
        file,
        line,
        message_buffer
    );

    if (level == LOG_LEVEL_FATAL) {
        exit(1);
    }
}
