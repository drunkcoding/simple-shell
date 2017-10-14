#ifndef __SHELLOPT_H__
#define __SHELLOPT_H__
// I/O headers
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>

//# define MALLCHECK(x) if (!x) return (-1);
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define PIPE_TOK_DELIM "|\t\r\n\a"
#define LSH_RL_BUFSIZE 1024
#define LSH_CMD_BUFSIZE 32
#endif

#ifndef __FUNC_SHELL__
#define __FUNC_SHELL__
// main loop operation
char *lsh_read_line(void);
char **lsh_split_line(char *line, char *delim);
//void array_cpy(char **in, char **out, int l, int r);
//void array_free(char **arr);
void msg_prompt(void);
int error_handler(int code);
//int count_pipe(char **arr);
//char* strjoin(char *s1, char *s2);


#define MALLOC(ptr, num, type) {\
    ptr = (type *)malloc((num) * sizeof(type));\
    if (!ptr) fprintf(stderr, "ve482sh: Allocation error\n");\
}
#define REALLOC(ptr, ptr_old, num, type, std_size) {\
    num += std_size;\
    ptr_old = ptr;\
    ptr = (type *) realloc(ptr, num * sizeof(type));\
    if (!ptr)\
    {\
        free(ptr_old);\
        fprintf(stderr, "ve482ssh: Allocation error\n");\
        ptr = NULL;\
    }\
}

#endif
