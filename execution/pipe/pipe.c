#include "../../minishell.h"

int	first_cmd(int *fd, t_ast *the_cmd, t_env_export *env_export)
{
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		return (sys_error(the_cmd->argv[0], the_cmd->argv[1]));
	if (the_cmd->redir)
		return (simple_redir(the_cmd, env_export));
	return (ft_cmd(the_cmd, env_export));
}

int	last_cmd(int *fd, t_ast *the_cmd, t_env_export *env_export)
{
	dup2(1, STDOUT_FILENO);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (sys_error(the_cmd->argv[0], the_cmd->argv[1]));
	if (the_cmd->redir)
		return (simple_redir(the_cmd, env_export));
	return (ft_cmd(the_cmd, env_export));
}

void func()
{
	// commands
	int fd = 0;
	while(commands)
	{
		fd = ft_pipe(hdfk, fd);
	}
}

int	ft_pipe(t_ast *s_ast, t_env_export *env_export, )
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
			{

				first_cmd(fd, the_cmd, env_export);
			}
			else if (i == s_ast->nbr_pipes)
			{
				last_cmd(fd, the_cmd, env_export);
				close(fd[0]);
			}
			exit(0);
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	while (wait(NULL) != -1);
	return (EXIT_SUCCESS);
}