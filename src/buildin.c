#include "shell.h"

int lsh_cd(char **args)
{
    
    if (chdir(args[1]) != 0)
    {
        perror("ve482sh");
    }
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}

int lsh_pwd(char **args)
{
    char *buff;
    buff = getcwd(NULL, 0);
    fprintf(stdout, "%s\n", buff);
    fflush(stdout);
    free(buff);
    return 1;
}
