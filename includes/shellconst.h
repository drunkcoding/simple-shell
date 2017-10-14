#ifndef __CONST_SHELL__
#define __CONST_SHELL__
//constants error
static char *msg_err[] = {
    "ve482sh: Lack of output file argument\n",
    "ve482sh: Lack of input file argument\n",
    "ve482sh: Cannot open file\n",
    "ve482sh: Allocation error\n",
    "ve482sh: Error in opening pipe"
};
enum error_code
{
    NO_OUTPUT_FILE,
    NO_INPUT_FILE,
    FILE_OPEN_ERR,
    MEM_ALLOC_ERR,
    OPEN_PIPE_ERR
};
#endif
