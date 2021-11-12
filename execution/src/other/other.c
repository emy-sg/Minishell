#include "../../../minishell.h"

int	other(t_ast *s_ast, t_env_export *env_export)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
		run_cmd(s_ast, env_export);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
		g_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}
