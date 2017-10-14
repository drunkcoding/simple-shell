#include "shell.h"

void lsh_loop(void)
{
    char *line;
    char **pipe_args, **args;
    int status = 1, i = 0, numpipe;
    int pipe_read, buildin_flag;
    signal(SIGINT, signal_handler);
    while (status == 1)
    {
        int pfd[2];
        msg_prompt();
        line = lsh_read_line();
        //fprintf(stderr,"%s\n", line);
        pipe_args = lsh_split_line(line, PIPE_TOK_DELIM);
        for (i = 0; pipe_args[i] != NULL; i++);
        numpipe = i - 1;

        for (i = 0; pipe_args[i] != NULL; i++)
        {
            //fprintf(stderr, "%s\n", pipe_args[i]);
            buildin_flag = 0;
            args = lsh_split_line(pipe_args[i], LSH_TOK_DELIM);
            //for (int k = 0; args[k] != NULL; k++)
            //fprintf(stderr, "%d:%s\n", k, args[k]);
            if (args[0] == NULL)
            {
                status = 1;
                break;
            }
            for (int j = 0; j < lsh_num_builtins(); j++)
                if (strcmp(args[0], builtin_str[j]) == 0)
                {
                    status = (*builtin_func[j])(args);
                    buildin_flag = 1;
                }
            if (buildin_flag)
            {
                free(args);
                break;
            }
            pid_t pid, wpid;
            char **new_args = NULL;
            if (i < numpipe)
            {
                if (pipe(pfd) < 0)
                    break;
            }
            pid = fork();
            //status = lsh_execute(args, pipe_fd, numpipe, i);
            if (pid < 0)
            {
                fprintf(stderr, "ve482sh: Child process could not be created\n");
                break;
            }
            signal(SIGINT, proc_signal_handler);
            if (pid == 0)
            {

                // Child process
                new_args = fileIO(args);
                if (numpipe > 0)
                {
                    //fprintf(stderr, "pfd[0]:%d, pfd[1]:%d, read:%d\n", pfd[0], pfd[1], pipe_read);

                    if (i != 0)
                    {
                        dup2(pipe_read, STDIN_FILENO);
                        close(pipe_read);
                    }
                    if (i < numpipe)
                    {
                        close(pfd[0]);
                        dup2(pfd[1], STDOUT_FILENO);
                        close(pfd[1]);
                    }
                    //if (i == numpipe) close(pipe_read);
                }
                //fprintf(stderr, "after fileio\n");
                
                if (execvp(new_args[0], new_args) == -1)
                {
                    fprintf(stderr, "%s: Command not found\n", new_args[0]);
                }
                //fprintf(stderr, "after execvp\n");
            }
            //else
            if (i != 0)
                close(pipe_read);
            if (i < numpipe)
            {
                close(pfd[1]);
                pipe_read = pfd[0];
            }
            //if (i == numpipe) close(pipe_read);
            free(new_args);
            free(args);
        }
        while (wait(NULL) > 0)
            ;

        free(line);
        line = NULL;
        free(pipe_args);
        pipe_args = NULL;
    }
}
