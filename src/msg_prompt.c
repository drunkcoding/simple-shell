#include "shellopt.h"

void msg_prompt(void)
{
    char buff[] = "ve482sh $ ";
    fprintf(stdout, "%s", buff);
    fflush(stdout);
}
