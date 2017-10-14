#include "shellopt.h"

char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0, stream_flag = 0;
    char *buffer = NULL;
    int c;
    MALLOC(buffer, bufsize, char);
    if (!buffer)
    {
        fprintf(stderr, "ve482sh: Allocation error\n");
        return NULL;
    }

    while (1)
    {
        // Read a character
        c = getchar();
        switch (c)
        {
        case '\n':
            if (stream_flag)
            {
                fprintf(stderr, "> ");
                fflush(stderr);
                position--;
                break;
            }
            else
            {
                buffer[position] = '\0';
                return buffer;
            }
        case EOF:
            if (position == 0)
            {
                free(buffer);
                fprintf(stdout, "\n");
                fflush(stdout);
                exit(EXIT_SUCCESS);
            }
            position--;
            break;
            //exit(EXIT_SUCCESS);
        default:
            buffer[position] = c;
            if ((c=='>') || (c=='<') || (c=='|'))
                stream_flag = 1;
            else if ((c!=' ') || (c!='\t') || (c!='\n'))
                stream_flag = 0;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize)
        {
            fprintf(stderr, "ve482sh: Command line length exceeds\n");
            exit(EXIT_FAILURE);
        }
    }
}

char **lsh_split_line(char *line, char *delim)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = (char**) malloc(bufsize * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, delim);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            REALLOC(tokens, tokens_backup, bufsize, char*, LSH_TOK_BUFSIZE);
        }

        token = strtok(NULL, delim);
    }
    tokens[position] = NULL;
    return tokens;
}
