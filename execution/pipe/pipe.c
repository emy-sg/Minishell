#include "../../minishell.h"

int	first_cmd(int *fd, t_ast *the_cmd, t_env_export *env_export)
{
	int	stdin_fd;

	stdin_fd = dup(0);
	if (dup2(0, STDIN_FILENO) < 0)
		return (sys_error(the_cmd->argv[0], the_cmd->argv[1]));
	close(stdin_fd);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		return (sys_error(the_cmd->argv[0], the_cmd->argv[1]));
	if (the_cmd->redir)
		return (simple_redir(the_cmd, env_export));
	return (ft_cmd(the_cmd, env_export));
}

int	last_cmd(int *fd, t_ast *the_cmd, t_env_export *env_export)
{
	int	stdout_fd;

	stdout_fd = dup(1);
	if (dup2(stdout_fd, STDOUT_FILENO) < 0)
		return (sys_error(the_cmd->argv[0], the_cmd->argv[1]));
	close(stdout_fd);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (sys_error(the_cmd->argv[0], the_cmd->argv[1]));
	if (the_cmd->redir)
		return (simple_redir(the_cmd, env_export));
	return (ft_cmd(the_cmd, env_export));
}

int	ft_pipe(t_ast *s_ast, t_env_export *env_export)
{
	t_ast	*the_cmd;
	pid_t	pid;
	int		fd[2];
	int		i;

	i = 0;
	the_cmd = s_ast;
	if (pipe(fd) == -1)
		return (sys_error(NULL, NULL));
	while (i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_cmd(fd, the_cmd, env_export);
			else if (i == s_ast->nbr_pipes)
				last_cmd(fd, the_cmd, env_export);
			exit(0);
		}
		i++;
	}
	while (wait(NULL) > 0);
	return (EXIT_SUCCESS);
}