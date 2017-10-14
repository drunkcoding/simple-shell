#include "shell.h"

int main(int argc, char **argv)
{
    // Run command loop.
    lsh_loop();

    // Perform any shutdown/cleanup.
    return EXIT_SUCCESS;
}
