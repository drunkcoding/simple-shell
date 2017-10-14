#include "shell.h"

int file_handler(char **args, char *operator, int i)
{
    int flag;
    char file[1024], opt[1024], temp[1024];
    if (strstr(args[i], operator) != NULL)
    {
        if (strcmp(args[i], operator) == 0)
        {
            if (args[i + 1] == NULL)
                return error_handler(NO_OUTPUT_FILE);
            //diff -y - 1.txt < 1.txtfprintf(stderr, "op: %s, %s\n", args[i+1], operator);
            flag = file_open(args[i + 1], operator);
            return flag;
        }
        /*
        else
        {
            int k = 0, j = 0;
            for (k = 0; (opt[k] = args[i][k]) != operator[0]; k++);
            opt[k] = '\0';
            if (strlen(operator) == 2) 
                if (strcmp(operator, ">") == 0)
                    return 0;
            strcpy(temp, args[i]+k);
            strcpy(args[i], temp);
            for (j = 0; ((file[j] = args[i][k]) != '>') \
            || ((file[j] = args[i][k]) != '<'); k++, j++);
            file[j] = '\0';
            flag = file_open(file, operator);
        }
        */
    }
    return 0;
}

char **fileIO(char *args[])
{
    int i = 0, position = 0, bufsize = LSH_CMD_BUFSIZE;
    int flag_out, flag_in, flag_app;
    char **new_args = NULL, **ptr_tmp;
    MALLOC(new_args, LSH_CMD_BUFSIZE, char *);
    while (args[i] != NULL)
    {
        flag_app = file_handler(args, ">>", i);
        flag_out = file_handler(args, ">", i);
        flag_in = file_handler(args, "<", i);
        //fprintf(stderr, "%s, %d, %d, %d\n", args[i], flag_app, flag_out, flag_in);
        
        if ((flag_app > 0) || (flag_out > 0) || (flag_in > 0))
        {
            //right = i;
            i+=2;
            continue;
        }
        //fprintf(stderr, "not match\n");
        if ((flag_app == 0) && (flag_out == 0) && (flag_in == 0))
        {
            MALLOC(new_args[position], strlen(args[i])+1, char);
            strcpy(new_args[position], args[i]);
            position++;
            if (position >= bufsize)
                REALLOC(new_args, ptr_tmp, bufsize, char *, LSH_CMD_BUFSIZE);
        }
        i++;
    }
    new_args[position] = NULL;
    return new_args;
}

int file_open(char *file, char *opt)
{
    int fd;
    // Append
    if (strcmp(">>", opt) == 0)
    {
        fd = open(file, O_APPEND | O_WRONLY);
        if (fd < 0)
            return error_handler(FILE_OPEN_ERR);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        return 1;
    }
    // New file
    if (strcmp(">", opt) == 0)
    {
        fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0600);
        if (fd < 0)
            return error_handler(FILE_OPEN_ERR);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        return 1;
    }
    // Input file
    if (strcmp("<", opt) == 0)
    {
        fd = open(file, O_RDONLY);
        if (fd < 0)
            return error_handler(FILE_OPEN_ERR);
        dup2(fd, STDIN_FILENO);
        close(fd);
        return 1;
    }
    return 0;
}
