#include "../../minishell.h"

//int	read_fd(int *fd)
//{
//	if (dup2(*fd, STDIN_FILENO) < 0)
//		return (EXIT_FAILURE);
//	return (EXIT_SUCCESS);
//}

//int	write_fd(int pipe_fd)
//{
//	if (dup2(pipe_fd, STDOUT_FILENO) < 0)
//		return (EXIT_FAILURE);
//	return (EXIT_SUCCESS);
//}

int	ft_cmd_pipe(t_ast *the_cmd, t_env_export *env_export)
{
	if (the_cmd->redir)
		return (ft_redir(the_cmd, env_export));
	return (ft_cmd(the_cmd, env_export));
}

int	ft_pipe(t_ast *s_ast, t_env_export *env_export)
{
	t_ast	*the_cmd;
	pid_t	pid;
	int		**pipe_fd;
	int		i;

	i = 0;

	the_cmd = s_ast;
	pipe_fd = (int **)ft_fcalloc(sizeof(int *), s_ast->nbr_pipes);
	if (pipe_fd == NULL)
		return (sys_error(NULL, NULL));
	while(i <= s_ast->nbr_pipes)
	{
		the_cmd = the_cmd->child_cmd;
		if (i < s_ast->nbr_pipes)
		{
			pipe_fd[i] = (int *)ft_fcalloc(sizeof(int), 2);
			if (pipe_fd[i] == NULL)
			{
				free_double_int(pipe_fd);
				return (sys_error(NULL, NULL));
			}
			if (pipe(pipe_fd[i]) == -1)
			{
				free_double_int(pipe_fd);
				return (sys_error(NULL, NULL));
			}
		}
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				close(pipe_fd[i][0]);
				dup2(0, STDIN_FILENO);
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			}
			else if (i == s_ast->nbr_pipes)
			{
				close(pipe_fd[i - 1][1]);
				dup2(pipe_fd[i - 1][0], STDIN_FILENO);
				dup2(1, STDOUT_FILENO);
			}
			else
			{
				dup2(pipe_fd[i - 1][0], STDIN_FILENO);
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			}
			if (ft_strcstr(the_cmd->argv[0], "exit") == NULL)
				ft_cmd_pipe(the_cmd, env_export);
			if (i < s_ast->nbr_pipes)
			{
				close(pipe_fd[i][0]);
				close(pipe_fd[i][1]);
			}
			//ft_putstr_fd(the_cmd->argv[0], 2);
			//ft_putstr_fd(" : [DONE]\n", 2);
			exit(0);
		}
		if (i < s_ast->nbr_pipes)
			close(pipe_fd[i][1]);
		i++;
	}
	while (wait(NULL) != -1);
	return (EXIT_SUCCESS);
}