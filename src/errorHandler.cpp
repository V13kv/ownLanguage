#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/errorHander.hpp"

void onError(char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);

    exit(EXIT_FAILURE);
}
