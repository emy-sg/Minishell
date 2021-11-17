#include "../../minishell.h"

void	terminate_processe(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	terminate_here_doc(int sig)
{
	int exit_value;

	exit_value = 125 + sig;
	global.here_doc = 1;
	exit(exit_value);
}