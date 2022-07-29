#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/errorHander.hpp"

[[noreturn]] void onError(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    exit(EXIT_FAILURE);
}
