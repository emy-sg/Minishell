#include "../../minishell.h"

int	ft_cmd_pipe(t_ast *the_cmd, t_env_export *env_export)
{
	if (ft_strcstr(the_cmd->argv[0], "exit") == NULL)
	{
		if (the_cmd->redir)
			return (ft_redir(the_cmd, env_export));
		return (ft_cmd(the_cmd, env_export));
	}
	return (EXIT_SUCCESS);
}

int	ft_pipe(t_ast *s_ast, t_env_export *env_export)
{
	t_ast	*the_cmd;
	pid_t	pid;
	int		pipe_fd[2];
	int		help_fd;
	int		i;
	int		status;

	i = 0;

	the_cmd = s_ast;
	help_fd = dup(0);
	while(i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (pipe(pipe_fd) == -1)
			return (sys_error(NULL, NULL));
		pid = fork();
		if (pid == 0)
		{
			dup2(help_fd, STDIN_FILENO);
			if (i == s_ast->nbr_pipes)
				dup2(1, STDOUT_FILENO);
			else
				dup2(pipe_fd[1], STDOUT_FILENO);
			ft_cmd_pipe(the_cmd, env_export);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(help_fd);
			exit(0);
		}
		close(help_fd);
		help_fd = dup(pipe_fd[0]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		i++;
	}
	ft_putnbr_fd(pid, 2);
	ft_putstr_fd("\n", 2);
	while (waitpid(pid, &status, 0) != -1)
	{
		ft_putnbr_fd(status, 2);
		ft_putstr_fd("\n", 2);
	}
	ft_putnbr_fd(status, 2);
	ft_putstr_fd("\n", 2);
	if (WEXITSTATUS(status) != 0)
		g_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}