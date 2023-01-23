#include "core/error_list.h"

const char *error_names[] = {
    "OK",
    "Failed",
    "Window error",
    "Context error",
    "Input error"
};

// TODO: Not a nice way to print error names in log_output in logger.c
const char *error_strings[] = {
    "",
    "Failed: ",
    "Window error: ",
    "Context error: ",
    "Input error: "
};