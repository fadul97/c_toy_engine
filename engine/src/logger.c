#include "core/logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/* Color only works on Linux
 * TODO: Add color/Refactor for Win32 and MacOS */
void log_output(LogLevel level, enum Error err, const char* message, ...)
{
    // Setup for sprintf and then printf
    char out_msg[1000];
    char out_msg2[1000];
    memset(out_msg, 0, sizeof(out_msg));

    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_msg, 1000, message, arg_ptr);

    /* Colors(Linux only) */
    const char *default_color = "\033[0m";

    // Bold red, Red, Orange, Blue, Green
    const char *color_strings[5] = {
        "\033[1;31m", "\033[0;31m", "\033[0;33m", "\033[0;34m", "\033[0;32m"
    };
    
    const char* level_strings[5] = {
        "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[DEBUG]: ", "[INFO]: "
    };

    // FATAL or ERROR log
    if(level < 2)
    {
        sprintf(out_msg2, "%s%s%s", level_strings[level], error_strings[err], out_msg);
        printf("%s%s%s\n", color_strings[level], out_msg2, default_color);
        return;
    }

    sprintf(out_msg2, "%s%s", level_strings[level], out_msg);
    printf("%s%s%s\n", color_strings[level], out_msg2, default_color);
}
