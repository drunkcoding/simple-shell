#include "shell.h"

void proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		fprintf(stdout, "\n");
		msg_prompt();
		fflush(stdout); 
		signal(SIGINT, proc_signal_handler);
	}
}

void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		fprintf(stdout, "\n");
		msg_prompt();
		fflush(stdout); 
		signal(SIGINT, signal_handler);
	}
}
