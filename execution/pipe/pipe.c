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
	pid_t	*pidd;
	int		pipe_fd[2];
	int		in_fd;
	int		i;

	i = 0;
	pidd = (int *)ft_calloc(sizeof(int), s_ast->nbr_pipes + 1);
	the_cmd = s_ast;
	while(i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (i < s_ast->nbr_pipes && pipe(pipe_fd) == -1)
			return (sys_error(NULL, NULL));
		pid = fork();
		if (pid != 0)
			pidd[i] = pid;
		if (pid == 0)
		{
			//ft_putstr_fd("child : in_fd = ", 2);
			//ft_putnbr_fd(in_fd, 2);
			//ft_putstr_fd("\n", 2);
			close(pipe_fd[0]);
			if (i == 0)
			{
				dup2(0, STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
			}
			if (i == s_ast->nbr_pipes)
			{
				dup2(in_fd, STDIN_FILENO);
				dup2(1, STDOUT_FILENO);
			}
			else
			{
				dup2(in_fd, STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
			}
			ft_cmd_pipe(the_cmd, env_export);
			close(pipe_fd[1]);
			close(in_fd);
			exit(g_status);
		}
		//ft_putstr_fd("parent : pipe_fd[0] = ", 2);
		//ft_putnbr_fd(pipe_fd[0], 2);
		//ft_putstr_fd("\n", 2);
		close(in_fd);
		in_fd = pipe_fd[0];
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		i++;
	}
	ft_putstr_fd("parent : ", 2);
	ft_putstr_fd(" | pid = ", 2);
	ft_putnbr_fd(pid, 2);
	ft_putstr_fd("\n", 2);
	//waitpid(-1,NULL, 0);
	//while (wait(NULL) != -1);
	int status;
	i = 0;
	while (i <= s_ast->nbr_pipes)
	{
		waitpid(pidd[i], &status, 0);
		i++;
	}
	if (WEXITSTATUS(status) != 0)
		g_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}