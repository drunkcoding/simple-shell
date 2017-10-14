#ifndef __SHELL_H__
#define __SHELL_H__
// program header
#include <dirent.h>
#include "shellopt.h"
#include "shellconst.h"
#endif

#ifndef __BASIC_FUNC__
#define __BASIC_FUNC__
// handler function
void lsh_loop(void);
int lsh_execute(char **args, int *pfd, int numpipe, int index);
int lsh_launch(char **args, int *pfd, int numpipe, int index);
int lsh_exit(char **args);
int lsh_cd(char **args);
int lsh_pwd(char **args);
void proc_signal_handler(int signo);
void signal_handler(int signo);
char **fileIO(char *args[]);
int file_open(char *file, char *opt);

static char *builtin_str[] = {
    "exit",
    "cd",
    "pwd"};

static int (*builtin_func[])(char **) = {
    &lsh_exit,
    &lsh_cd,
    &lsh_pwd};

static int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

#endif


