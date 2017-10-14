#include "shell.h"

int error_handler(int code)
{
    fprintf(stderr, "%s", msg_err[code]);
    fflush(stderr);
    return -1;
}
