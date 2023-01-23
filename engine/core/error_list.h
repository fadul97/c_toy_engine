#ifndef ERROR_LIST_H
#define ERROR_LIST_H

enum Error
{
    OK,
    FAILED,
    ERR_WINDOW,
    ERR_CONTEXT,
    ERR_INPUT
};

extern const char *error_names[];
extern const char *error_strings[];

#endif // ERROR_LIST_H